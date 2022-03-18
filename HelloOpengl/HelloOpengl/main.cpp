#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <math.h>

void drawSphere(double r, int lats, int longs){
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f( 255  ,12, 0);
        for(i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
            double z0  = sin(lat0);
            double zr0 =  cos(lat0);

            double lat1 = M_PI * (-0.5 + (double) i / lats);
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            glBegin(GL_QUAD_STRIP);
            for(j = 0; j <= longs; j++) {
                double lng = 2 * M_PI * (double) (j - 1) / longs;
                double x = cos(lng);
                double y = sin(lng);

                glNormal3f(x * zr0, y * zr0, z0);
                glVertex3f(r * x * zr0, r * y * zr0, r * z0);
                glNormal3f(x * zr1, y * zr1, z1);
                glVertex3f(r * x * zr1, r * y * zr1, r * z1);
            }
            glEnd();
        }
    
}
int display[2] = {1024,768};
void init(void){
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(180,(display[0]/display[1]),0.0,50.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glTranslatef(0,0,-10);
    glRotatef(60,0,1,1);
}



int main(void)
{
    GLFWwindow* window;
    
    if(!glfwInit())
        return -1;
    
    window = glfwCreateWindow(display[0],display[1],"sometitle",NULL,NULL);
    
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    init();
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        drawSphere(10,800,800);
        glRotatef(8,1,4,1);
        glfwSwapBuffers(window);
        glfwPollEvents();
        usleep(10000);
    }
    glfwTerminate();
    return 0;
    
    
}
