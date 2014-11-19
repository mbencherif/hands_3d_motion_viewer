#define GL_GLEXT_PROTOTYPES
#include <QtOpenGL>
#include <glwidget.h>





void GLWidget::myOpenGL_Flags()
{

        ////////////////////////////////////////
        //// Alliws den kanei swsto Culling !!!!
        ////////////////////////////////////////
        glFrontFace(GL_CW);  // GL_CW​ // GL_CCW
        ////////////////////////////////////////
        ////////////////////////////////////////

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LINE_SMOOTH);

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glDisable(GL_CULL_FACE);

        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

        glEnable(GL_POINT_SMOOTH);

        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void GLWidget::OpenGL_Lights_Turn_ON()
{

        //////////////////////
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        //////////////////////

        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////

        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        GLfloat cyanDiff[] = {0.f, .8f, .8f, 0.5f};     glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyanDiff  );
        GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};     glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,            white     );
        GLfloat shininess[] = {50.0f};                  glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS,           shininess );

        GLfloat light_position_0[] = { -1.0, -1.0, 1.0, 0.0 };

        glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);


        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////

        GLfloat light1_ambient[]  = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light1_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv( GL_LIGHT1, GL_AMBIENT,  light1_ambient);
        glLightfv( GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light1_specular);

        glLightf(  GL_LIGHT1, GL_CONSTANT_ATTENUATION,  1.5 );
        glLightf(  GL_LIGHT1, GL_LINEAR_ATTENUATION,    0.5 );
        glLightf(  GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2 );

        glLightf(  GL_LIGHT1, GL_SPOT_CUTOFF,    45.0);
        glLightf(  GL_LIGHT1, GL_SPOT_EXPONENT,  5.0);

        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////

        GLfloat light2_ambient[]  = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light2_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv( GL_LIGHT2, GL_AMBIENT,  light2_ambient);
        glLightfv( GL_LIGHT2, GL_DIFFUSE,  light2_diffuse);
        glLightfv( GL_LIGHT2, GL_SPECULAR, light2_specular);

        glLightf(  GL_LIGHT2, GL_CONSTANT_ATTENUATION,  1.5 );
        glLightf(  GL_LIGHT2, GL_LINEAR_ATTENUATION,    0.5 );
        glLightf(  GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2 );

        glLightf(  GL_LIGHT2, GL_SPOT_CUTOFF,    45.0);
        glLightf(  GL_LIGHT2, GL_SPOT_EXPONENT,  9.0);

        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////

        GLfloat light3_ambient[]  = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light3_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light3_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv( GL_LIGHT3, GL_AMBIENT,  light3_ambient);
        glLightfv( GL_LIGHT3, GL_DIFFUSE,  light3_diffuse);
        glLightfv( GL_LIGHT3, GL_SPECULAR, light3_specular);

        glLightf(  GL_LIGHT3, GL_CONSTANT_ATTENUATION,  1.5 );
        glLightf(  GL_LIGHT3, GL_LINEAR_ATTENUATION,    0.5 );
        glLightf(  GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.2 );

        glLightf(  GL_LIGHT3, GL_SPOT_CUTOFF,    45.0);
        glLightf(  GL_LIGHT3, GL_SPOT_EXPONENT,  5.0);

        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////

        GLfloat light4_ambient[]  = { 0.2, 0.2, 0.2, 1.0 };
        GLfloat light4_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light4_specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv( GL_LIGHT4, GL_AMBIENT,  light4_ambient);
        glLightfv( GL_LIGHT4, GL_DIFFUSE,  light4_diffuse);
        glLightfv( GL_LIGHT4, GL_SPECULAR, light4_specular);

        glLightf(  GL_LIGHT4, GL_CONSTANT_ATTENUATION,  1.5 );
        glLightf(  GL_LIGHT4, GL_LINEAR_ATTENUATION,    0.5 );
        glLightf(  GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.2 );

        glLightf(  GL_LIGHT4, GL_SPOT_CUTOFF,    45.0);
        glLightf(  GL_LIGHT4, GL_SPOT_EXPONENT,  9.0);

        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        GLfloat light1_position[] = { -1.0, -1.0, -1.0, 0.0 };
        GLfloat light1_spot_dir[] = { +1.0, +1.0, +0.0 };
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        GLfloat light2_position[] = { +1.0, +1.0, -1.0, 0.0 };
        GLfloat light2_spot_dir[] = { -1.0, -1.0, +0.0 };
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        GLfloat light3_position[] = { +1.0, +1.0, +1.0, 0.0 };
        GLfloat light3_spot_dir[] = { -1.0, -1.0, +0.0 };
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        GLfloat light4_position[] = { -1.0, -1.0, +1.0, 0.0 };
        GLfloat light4_spot_dir[] = { +1.0, +1.0, +0.0 };
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////
        glLightfv( GL_LIGHT1, GL_POSITION,       light1_position);
        glLightfv( GL_LIGHT2, GL_POSITION,       light2_position);
        glLightfv( GL_LIGHT3, GL_POSITION,       light3_position);
        glLightfv( GL_LIGHT4, GL_POSITION,       light4_position);

        glLightfv( GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_dir);
        glLightfv( GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_dir);
        glLightfv( GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_dir);
        glLightfv( GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_dir);
        //////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////


                    //////////////////////
                    //////////////////////
                    glDisable(GL_LIGHT0 );
                    //////////////////////
                    glEnable( GL_LIGHT1 );
                    glEnable( GL_LIGHT2 );
                    glEnable( GL_LIGHT3 );
                    glEnable( GL_LIGHT4 );
                    //////////////////////
                    //////////////////////

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GLWidget::OpenGL_Lights_Turn_OFF()
{
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glDisable(GL_LIGHT4);
        glDisable(GL_LIGHT5);
        glDisable(GL_LIGHT6);
        glDisable(GL_LIGHT7);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void GLWidget::myRender_HANDLE_LIGHTS_and_FilledNonFilled()
{

        if (_myRender_MESH_FILL)
        {
                glShadeModel(GL_SMOOTH);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                glEnable(GL_DEPTH_TEST);
                glDepthMask(GL_TRUE);
                glDepthFunc(GL_LESS);

                OpenGL_Lights_Turn_ON();
        }
        else
        {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                glDisable(GL_DEPTH_TEST);

                OpenGL_Lights_Turn_OFF();
        }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
