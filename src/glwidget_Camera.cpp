#include <glwidget.h>




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void GLWidget::cameraTranslate( double dz )
{

    ///////////////////////////////////////////////////////
    CameraSet *pCameraSet = &(tracker->sequence.cameraSet);
    /////////////////////////////////////////////////////////////////////////
    ModelSet  *pModelSet  = &(tracker->sequence.posedAnimations[0].modelSet);
    /////////////////////////////////////////////////////////////////////////

    Eigen::MatrixXd AAA = Eigen::MatrixXd::Identity(4,4);

    AAA(2,3) = -dz / 6.0;

    pCameraSet->RT_4x4_custom = AAA * pCameraSet->RT_4x4_custom;
    this->spinCenter4D_curr   =       pCameraSet->RT_4x4_custom * pModelSet->centroid4D_curr;

    ////////////////////////////////////////////////
    pCameraSet->setModelViewFrom_RT_customMat_4_4();
    ////////////////////////////////////////////////

}



void GLWidget::cameraTranslate( double dx, double dy )
{

    ///////////////////////////////////////////////////////
    CameraSet *pCameraSet = &(tracker->sequence.cameraSet);
    /////////////////////////////////////////////////////////////////////////
    ModelSet  *pModelSet  = &(tracker->sequence.posedAnimations[0].modelSet);
    /////////////////////////////////////////////////////////////////////////

    Eigen::MatrixXd AAA = Eigen::MatrixXd::Identity(4,4);

    AAA(0,3) = dx;
    AAA(1,3) = dy;

    pCameraSet->RT_4x4_custom = AAA * pCameraSet->RT_4x4_custom;
    this->spinCenter4D_curr   =       pCameraSet->RT_4x4_custom * pModelSet->centroid4D_curr;

    ////////////////////////////////////////////////
    pCameraSet->setModelViewFrom_RT_customMat_4_4();
    ////////////////////////////////////////////////

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void GLWidget::cameraRotate(int mousePos_X, int mousePos_Y)
{

    ///////////////////////////////////////////////////////
    CameraSet *pCameraSet = &(tracker->sequence.cameraSet);
    ///////////////////////////////////////////////////////

    int www = tracker->sequence.videoSequence.frameWidth;
    int hhh = tracker->sequence.videoSequence.frameHeight;

    // scale points to -1 => 1
    float x1 = 2 * (float)     lastMousePos.x()  / (float)www - 1;
    float y1 = 2 * (float)(hhh-lastMousePos.y()) / (float)hhh - 1;
    float x2 = 2 * (float)         mousePos_X    / (float)www - 1;
    float y2 = 2 * (float)(hhh-    mousePos_Y)   / (float)hhh - 1;

    // stupid safety // UnNeeded!!!
    x1 = qMax( -1.0f, qMin( x1, 1.0f ) );
    y1 = qMax( -1.0f, qMin( y1, 1.0f ) );
    x2 = qMax( -1.0f, qMin( x2, 1.0f ) );
    y2 = qMax( -1.0f, qMin( y2, 1.0f ) );

  //Eigen::MatrixXd rot = Eigen::MatrixXd::Identity(3,3);
    Eigen::MatrixXd rot;
                    rot = trackball( -x1,y1,-x2,y2);

    Eigen::MatrixXd AAA = Eigen::MatrixXd::Identity(4,4);
    Eigen::MatrixXd BBB = Eigen::MatrixXd::Identity(4,4);
    Eigen::MatrixXd CCC = Eigen::MatrixXd::Identity(4,4);

    AAA(0,3) = +spinCenter4D_curr[0];
    AAA(1,3) = +spinCenter4D_curr[1];
    AAA(2,3) = +spinCenter4D_curr[2];

    BBB(0,0) = rot(0,0); // copy rot as part of BBB
    BBB(0,1) = rot(0,1); // 3x3 = submatrix of 4x4
    BBB(0,2) = rot(0,2);

    BBB(1,0) = rot(1,0);
    BBB(1,1) = rot(1,1);
    BBB(1,2) = rot(1,2);

    BBB(2,0) = rot(2,0);
    BBB(2,1) = rot(2,1);
    BBB(2,2) = rot(2,2);

    CCC(0,3) = -spinCenter4D_curr[0];
    CCC(1,3) = -spinCenter4D_curr[1];
    CCC(2,3) = -spinCenter4D_curr[2];

    pCameraSet->RT_4x4_custom = AAA * BBB * CCC * pCameraSet->RT_4x4_custom;

    ////////////////////////////////////////////////
    pCameraSet->setModelViewFrom_RT_customMat_4_4();
    ////////////////////////////////////////////////
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following 2 functions are borrowed from Juergen Gall ////////////////////////////////////////////
// with minor modification changes                          ////////////////////////////////////////////
// (e.g. use of Eigen, or own methods)                      ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


// Simulate a track-ball.
//
// Project the points onto the virtual trackball,
// then figure out the axis of rotation, which is the cross
// product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
//
// This is a deformed trackball-- it is a trackball in the center,
// but is deformed into a hyperbolic sheet of rotation away from the center
// This particular function was chosen after trying out several variations.
//
// It is assumed that the arguments to this routine are in the range
// (-1.0 ... 1.0)


////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////    OK
////////////////////////////////////////////////////////////////////////////////////////////////////////

float GLWidget::tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = float( sqrt(x*x + y*y) );
    if (d < r * 0.70710678118654752440) {    /* Inside sphere */
        z = float( sqrt(r*r - d*d) );
    } else {           /* On hyperbola */
        t = float( r / 1.41421356237309504880 );
        z = float( t*t / d );
    }
    return z;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

Eigen::MatrixXd GLWidget::trackball(float p1x, float p1y, float p2x, float p2y)
{

  float TRACKBALLSIZE = 0.8;

  Eigen::MatrixXd rot = Eigen::MatrixXd::Identity(3,3);

    if (p1x == p2x && p1y == p2y) {
        /* Zero rotation */
        rot = Eigen::MatrixXd::Identity(3,3);
    }
    else {
      /*
       * First, figure out z-coordinates for projection of P1 and P2 to
       * deformed sphere
       */
      Eigen::Vector3d vec1;
      Eigen::Vector3d vec2;
      vec1(0) = p1x;
      vec1(1) = p1y;
      vec1(2) = tb_project_to_sphere(TRACKBALLSIZE,p1x,p1y);
      vec2(0) = p2x;
      vec2(1) = p2y;
      vec2(2) = tb_project_to_sphere(TRACKBALLSIZE,p2x,p2y);

      /*
       *  Now, we want the cross product of P1 and P2
       */
      Eigen::Vector3d ccc = vec1.cross(vec2);
      ccc.normalize();

      /*
       *  Figure out how much to rotate around that axis.
       */
      vec2 -= vec1;
      float t = ( vec2.norm() / (0.05*TRACKBALLSIZE) ); // TWEAK THIS // bigger value => smaller movement, more detailed

      /*
       * Avoid problems with out-of-control values...
       */
      if (t > 1.0) t = 1.0;
      if (t < -1.0) t = -1.0;
      ccc *= 0.05 * double( asin(t) );

      //rot = axis_to_rotation_matrix( phi, c);
      rot = MyMath::my_Rv_2_RM( ccc );
    }
    return rot;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


