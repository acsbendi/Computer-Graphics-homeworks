//=============================================================================================
// Szamitogepes grafika hazi feladat keret. Ervenyes 2018-tol.
// A //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sorokon beluli reszben celszeru garazdalkodni, mert a tobbit ugyis toroljuk.
// A beadott program csak ebben a fajlban lehet, a fajl 1 byte-os ASCII karaktereket tartalmazhat, BOM kihuzando.
// Tilos:
// - mast "beincludolni", illetve mas konyvtarat hasznalni
// - faljmuveleteket vegezni a printf-et kiveve
// - Mashonnan atvett programresszleteket forrasmegjeloles nelkul felhasznalni es
// - felesleges programsorokat a beadott programban hagyni!!!!!!!
// - felesleges kommenteket a beadott programba irni a forrasmegjelolest kommentjeit kiveve
// ---------------------------------------------------------------------------------------------
// A feladatot ANSI C++ nyelvu forditoprogrammal ellenorizzuk, a Visual Studio-hoz kepesti elteresekrol
// es a leggyakoribb hibakrol (pl. ideiglenes objektumot nem lehet referencia tipusnak ertekul adni)
// a hazibeado portal ad egy osszefoglalot.
// ---------------------------------------------------------------------------------------------
// A feladatmegoldasokban csak olyan OpenGL fuggvenyek hasznalhatok, amelyek az oran a feladatkiadasig elhangzottak
// A keretben nem szereplo GLUT fuggvenyek tiltottak.
//
// NYILATKOZAT
// ---------------------------------------------------------------------------------------------
// Nev    : Acs Bendeguz
// Neptun : ZDDCHE
// ---------------------------------------------------------------------------------------------
// ezennel kijelentem, hogy a feladatot magam keszitettem, es ha barmilyen segitseget igenybe vettem vagy
// mas szellemi termeket felhasznaltam, akkor a forrast es az atvett reszt kommentekben egyertelmuen jeloltem.
// A forrasmegjeloles kotelme vonatkozik az eloadas foliakat es a targy oktatoi, illetve a
// grafhazi doktor tanacsait kiveve barmilyen csatornan (szoban, irasban, Interneten, stb.) erkezo minden egyeb
// informaciora (keplet, program, algoritmus, stb.). Kijelentem, hogy a forrasmegjelolessel atvett reszeket is ertem,
// azok helyessegere matematikai bizonyitast tudok adni. Tisztaban vagyok azzal, hogy az atvett reszek nem szamitanak
// a sajat kontribucioba, igy a feladat elfogadasarol a tobbi resz mennyisege es minosege alapjan szuletik dontes.
// Tudomasul veszem, hogy a forrasmegjeloles kotelmenek megsertese eseten a hazifeladatra adhato pontokat
// negativ elojellel szamoljak el es ezzel parhuzamosan eljaras is indul velem szemben.
//=============================================================================================
#define _USE_MATH_DEFINES		// Van M_PI
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "utils.hpp"
#include "camera.hpp"
#include "opengl.hpp"
#include "butterfly.hpp"
#include "cursor.hpp"
#include "flowermanager.hpp"

const unsigned int windowWidth = 600, windowHeight = 600;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// You are supposed to modify the code from here...

// OpenGL major and minor versions
int majorVersion = 3, minorVersion = 3;

void getErrorInfo(unsigned int handle) {
    int logLen;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0) {
        auto * log = new char[logLen];
        int written;
        glGetShaderInfoLog(handle, logLen, &written, log);
        printf("Shader log:\n%s", log);
        delete log;
    }
}

// check if shader could be compiled
void checkShader(unsigned int shader, const char * message) {
    int OK;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &OK);
    if (!OK) {
        printf("%s!\n", message);
        getErrorInfo(shader);
    }
}

// check if shader could be linked
void checkLinking(unsigned int program) {
    int OK;
    glGetProgramiv(program, GL_LINK_STATUS, &OK);
    if (!OK) {
        printf("Failed to link shader program!\n");
        getErrorInfo(program);
    }
}

// vertex shader in GLSL
const char * textureVertexSource = R"(
	#version 330
    precision highp float;

	uniform mat4 MVP;			// Model-View-Projection matrix in row-major format

	layout(location = 0) in vec2 vertexPosition;	// Attrib Array 0
	layout(location = 1) in vec2 vertexUV;			// Attrib Array 1

	out vec2 texCoord;								// output attribute

	void main() {
		texCoord = (vertexPosition + vec2(0.31, -2.52)) / 0.8 ;											// copy texture coordinates
		gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0, 1) * MVP; 		// transform to clipping space
	}
)";

// fragment shader in GLSL
const char * textureFragmentSource = R"(
	#version 330
    precision highp float;

	uniform sampler2D textureUnit;

	in vec2 texCoord;			// variable input: interpolated texture coordinates
	out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

	void main() {
		fragmentColor = texture(textureUnit, texCoord);
	}
)";

// vertex shader in GLSL
const char * vertexSource = R"(
	#version 330
    precision highp float;

	uniform mat4 MVP;			// Model-View-Projection matrix in row-major format

	layout(location = 0) in vec2 vertexPosition;	// Attrib Array 0
	layout(location = 1) in vec3 vertexColor;	    // Attrib Array 1
	out vec3 color;									// output attribute

	void main() {
		color = vertexColor;														// copy color from input to output
		gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0, 1) * MVP; 		// transform to clipping space
	}
)";

// fragment shader in GLSL
const char * fragmentSource = R"(
	#version 330
    precision highp float;

	in vec3 color;				// variable input: interpolated color of vertex shader
	out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

	void main() {
		fragmentColor = vec4(color, 1); // extend RGB to RGBA
	}
)";

// 2D camera
Camera camera{};
vec2 cursor;

// handle of the shader program
unsigned int shaderProgram;
unsigned int textureShaderProgram;

Butterfly butterfly;
FlowerManager flowerManager;

// Initialization, create an OpenGL context
void onInitialization() {
    glViewport(0, 0, windowWidth, windowHeight);

    butterfly.create();
    flowerManager.create();

    // Create vertex shader from string
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader) {
        printf("Error in vertex shader creation\n");
        exit(1);
    }
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader, "Vertex shader error");

    // Create fragment shader from string
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader) {
        printf("Error in fragment shader creation\n");
        exit(1);
    }
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader, "Fragment shader error");

    shaderProgram = glCreateProgram();
    if (!shaderProgram) {
        printf("Error in shader program creation\n");
        exit(1);
    }
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Connect the fragmentColor to the frame buffer memory
    glBindFragDataLocation(shaderProgram, 0, "fragmentColor");	// fragmentColor goes to the frame buffer memory

    // program packaging
    glLinkProgram(shaderProgram);
    checkLinking(shaderProgram);


    // Create vertex shader from string
    unsigned int textureVertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!textureVertexShader) {
        printf("Error in vertex shader creation\n");
        exit(1);
    }
    glShaderSource(textureVertexShader, 1, &textureVertexSource, nullptr);
    glCompileShader(textureVertexShader);
    checkShader(textureVertexShader, "Vertex shader error");

    // Create fragment shader from string
    unsigned int textureFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!textureFragmentShader) {
        printf("Error in fragment shader creation\n");
        exit(1);
    }
    glShaderSource(textureFragmentShader, 1, &textureFragmentSource, nullptr);
    glCompileShader(textureFragmentShader);
    checkShader(textureFragmentShader, "Fragment shader error");

    textureShaderProgram = glCreateProgram();
    if (!textureShaderProgram) {
        printf("Error in shader program creation\n");
        exit(1);
    }
    glAttachShader(textureShaderProgram, textureVertexShader);
    glAttachShader(textureShaderProgram, textureFragmentShader);

    // Connect the fragmentColor to the frame buffer memory
    glBindFragDataLocation(textureShaderProgram, 0, "fragmentColor");	// fragmentColor goes to the frame buffer memory

    // program packaging
    glLinkProgram(textureShaderProgram);
    checkLinking(textureShaderProgram);
    // make this program run
    glUseProgram(textureShaderProgram);

}

void onExit() {
    glDeleteProgram(shaderProgram);
    glDeleteProgram(textureShaderProgram);
    printf("exit");
}

// Window has become invalid: Redraw
void onDisplay() {
    glClearColor(0, 1.0f, 0, 0);							// background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
    flowerManager.draw();
    butterfly.draw();
    glutSwapBuffers();									// exchange the two buffers
}

// Key of ASCII code pressed
void onKeyboard(unsigned char key, int, int) {
    if(key == 'a'){
        camera.wCx -= 0.1f;
    } else if(key == 'd'){
        camera.wCx += 0.1f;
    } else if(key == 'w'){
        camera.wCy += 0.1f;
    } else if(key == 's'){
        camera.wCy -= 0.1f;
    } else if(key == '1'){
        camera.wWx += 0.1f;
        camera.wWy += 0.1f;
    } else if(key == '2'){
        camera.wWx -= 0.1f;
        camera.wWy -= 0.1f;
    }
}

// Key of ASCII code released
void onKeyboardUp(unsigned char, int, int) {

}
bool leftButton = false;

// Move mouse with key pressed
void onMouseMotion(int pX, int pY) {
    if(leftButton) {
        float cX = 2.0f * pX / windowWidth - 1;    // flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        cursor = vec2(vec4(cX, cY) * camera.Pinv() * camera.Vinv());
    }
}

// Mouse click event
void onMouse(int button, int state, int pX, int pY) {
    if(state == GLUT_DOWN){
        float cX = 2.0f * pX / windowWidth - 1;    // flip y axis
        float cY = 1.0f - 2.0f * pY / windowHeight;
        vec4 clickInWorld = vec4(cX,cY) * camera.Pinv() * camera.Vinv();
        if(button == GLUT_LEFT_BUTTON){
            cursor = vec2(clickInWorld);
            leftButton = true;
        } else if(button == GLUT_RIGHT_BUTTON){
            flowerManager.addFlower(clickInWorld.v[0], clickInWorld.v[1]);
            leftButton = false;
        }
        glutPostRedisplay();     // redraw
    }
}

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
    static float tend = 0;
    const float dt = 0.01; // dt is ”infinitesimal”
    float tstart = tend;
    tend = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

    for(float t = tstart; t < tend; t += dt) { // NOLINT
        float Dt = fminf(dt, tend - t);
        butterfly.animate(Dt,tend);
    }
    glutPostRedisplay();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Do not touch the code below this line

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
#if !defined(__APPLE__)
    glutInitContextVersion(majorVersion, minorVersion);
#endif
    glutInitWindowSize(windowWidth, windowHeight);				// Application window is initially of resolution 600x600
    glutInitWindowPosition(100, 100);							// Relative location of the application window
#if defined(__APPLE__)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_3_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
    glutCreateWindow(argv[0]);

#if !defined(__APPLE__)
    glewExperimental = GL_TRUE;	// magic
    glewInit();
#endif

    printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
    printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
    printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
    printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    onInitialization();

    glutDisplayFunc(onDisplay);                // Register event handlers
    glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);
    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutMotionFunc(onMouseMotion);

    glutMainLoop();
    onExit();
    return 1;
}

