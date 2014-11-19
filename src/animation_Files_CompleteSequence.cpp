#include "animation.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Animation::poseMatrices_LoadFromFile( int frameNumberForReadOutput )
{

            ///////////////////////////
            readFromTXT( "dontPrint" );   // dontPrint  // print
            ///////////////////////////

            int fr = frameNumberForReadOutput;
            transform_ModelSet_MESHES(    fr );
            transform_ModelSet_SKELETONS( fr );
            calculate_RotationAxes(       fr );

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void Animation::poseMatrices_Clear()
{

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////

            for (int modelID=0; modelID<modelSet.totalModels; modelID++)
            {

                ////////////////////////////////////////////////////////////////////
                int NoOfFrames = movingModels[modelID].motionFrames.size();                if (NoOfFrames == 0)    return;       // SOS!!! - skaei stin arxi xwris afto - kaleitai apo arxiki anagnwsi Radios ;)  ???????????????????????????
                int NoOfBones  = movingModels[modelID].motionFrames[0].bones.size();
                ////////////////////////////////////////////////////////////////////

                for (int fr=0; fr<NoOfFrames; fr++)
                {
                        for (int b=0; b<NoOfBones; b++)
                        {
                                movingModels[modelID].motionFrames[fr].bones[b].name   = "";
                                movingModels[modelID].motionFrames[fr].bones[b].R      = Eigen::MatrixXd::Zero(3,3);
                                movingModels[modelID].motionFrames[fr].bones[b].T      = Eigen::MatrixXd::Zero(3,1);
                                movingModels[modelID].motionFrames[fr].bones[b].RT_3x4 = Eigen::MatrixXd::Zero(3,4);
                                movingModels[modelID].motionFrames[fr].bones[b].RT_4x4 = Eigen::MatrixXd::Zero(4,4);
                        }
                }
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////

            transform_ModelSet_MESHES(    1 );   // den exei simasia ti tha valw, ola einai midenika!
            transform_ModelSet_SKELETONS( 1 );   // den exei simasia ti tha valw, ola einai midenika!
            calculate_RotationAxes(       1 );   // den exei simasia ti tha valw, ola einai midenika!

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void Animation::readFromTXT( QString shouldPrint )
{

            /////////////////
            QString filename;
            /////////////////


            for (int modelID=0; modelID<modelSet.totalModels; modelID++)
            {

                        ////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////
                        filename = movingModels[modelID].PATH_complete_Motion_INput;
                        ////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////


                        //////////////////////////////////////////////////////////////
                        //////////////////////////////////////////////////////////////
                        int NoOfFrames = modelSet.models[modelID].totalSkeletonFrames;
                        int NoOfBones  = modelSet.models[modelID].totalBones;
                        //////////////////////////////////////////////////////////////
                        //////////////////////////////////////////////////////////////

                        movingModels[modelID].motionFrames.clear();
                        movingModels[modelID].motionFrames.resize( NoOfFrames );

                        for     (int fr=0; fr<NoOfFrames; fr++)
                        {
                            movingModels[modelID].motionFrames[fr].bones.clear();
                            movingModels[modelID].motionFrames[fr].bones.resize( NoOfBones );

                            for (int b=0; b<NoOfBones; b++)
                            {
                                movingModels[modelID].motionFrames[fr].bones[b].R      = Eigen::MatrixXd::Zero(3,3);
                                movingModels[modelID].motionFrames[fr].bones[b].T      = Eigen::MatrixXd::Zero(3,1);
                                movingModels[modelID].motionFrames[fr].bones[b].RT_3x4 = Eigen::MatrixXd::Zero(3,4);
                                movingModels[modelID].motionFrames[fr].bones[b].RT_4x4 = Eigen::MatrixXd::Zero(4,4);
                            }
                        }

                        movingModels[modelID].motionFrames.squeeze();

                        ////////////////////////////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////////////////////////////

                        QFile myFileREAD( filename );
                        myFileREAD.open(QIODevice::ReadOnly);

                        if(!myFileREAD.isOpen()){
                            qDebug() << "Animation::readFromTxt - Error, unable to open **" << filename << "** for input";
                            return;
                        }

                        QTextStream myStreamREAD(&myFileREAD);

                        ////////////////////////////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////////////////////////////

                        for (int b=0; b<NoOfBones; b++)
                        {

                                myStreamREAD >> movingModels[modelID].motionFrames[0].bones[b].name;
                                if (            movingModels[modelID].motionFrames[0].bones[b].name == "Lower")
                                {
                                    QString help1;
                                    QString help2;
                                    myStreamREAD >> help1;
                                    myStreamREAD >> help2;
                                    movingModels[modelID].motionFrames[0].bones[b].name = movingModels[modelID].motionFrames[0].bones[b].name + " " + help1 + " " + help2;
                                }

                                ////////////////////////////////////////////////////////////////////////////
                                ////////////////////////////////////////////////////////////////////////////
                                                                                                                                                            \
                                double inDouble;

                                for (int fr=0; fr<NoOfFrames; fr++)
                                {

                                        movingModels[modelID].motionFrames[fr].bones[b].name = movingModels[modelID].motionFrames[0].bones[b].name;

                                        for (int i=0; i<3; i++)
                                        {
                                            for (int j=0; j<3; j++)
                                            {
                                                myStreamREAD >> inDouble;       movingModels[modelID].motionFrames[fr].bones[b].R(i,j) = inDouble;
                                            }
                                        }
                                        for (int i=0; i<3; i++)
                                        {
                                                myStreamREAD >> inDouble;       movingModels[modelID].motionFrames[fr].bones[b].T(i) = inDouble;
                                        }

                                        /////////////////////////////////////////////////////////////////
                                        construct__RT_3x4__RT_4x4__basedOn__R_T__1bone( modelID, fr, b );
                                        /////////////////////////////////////////////////////////////////

                                }

                        }

                        ////////////////////////////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////////////////////////////

                        myFileREAD.close();

            } // for (int modelID=0; modelID<modelSet.totalModels; modelID++)

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////    PRINTER    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (shouldPrint == "print")
            {
                    for (int modelID=0; modelID<modelSet.totalModels; modelID++)
                    {
                                //////////////////////////////////////////////////////////////
                                int NoOfFrames = modelSet.models[modelID].totalSkeletonFrames;
                                int NoOfBones  = modelSet.models[modelID].totalBones;
                                //////////////////////////////////////////////////////////////

                                std::cout << "\n\n" << QString("RESULTS :)\n").toStdString() << std::endl;

                                for (int b=0; b<NoOfBones; b++)
                                {

                                        std::cout << "\n" << movingModels[modelID].motionFrames[0].bones[b].name.toStdString() << "\n" << std::endl;
                                        qDebug() << "Animation::readFromTXT\t" << movingModels[modelID].motionFrames[0].bones[b].name;

                                        ////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////////////////////////////////////////

                                        for (int fr=0; fr<NoOfFrames; fr++)
                                        {
                                                std::cout << movingModels[modelID].motionFrames[fr].bones[b].R << "\n" << std::endl;
                                                std::cout << movingModels[modelID].motionFrames[fr].bones[b].T << "\n" << std::endl;
                                        }

                                }

                    } // for (int modelID=0; modelID<modelSet.totalModels; modelID++)

            }


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Animation::construct__RT_3x4__RT_4x4__basedOn__R_T__1bone( int modelID, int fr, int b )
{

    movingModels[modelID].motionFrames[fr].bones[b].RT_3x4 << movingModels[modelID].motionFrames[fr].bones[b].R, movingModels[modelID].motionFrames[fr].bones[b].T;

    movingModels[modelID].motionFrames[fr].bones[b].RT_4x4 << movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(0,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(0,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(0,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(0,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(1,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(1,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(1,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(1,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(2,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(2,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(2,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_3x4(2,3),
                                                              0,                                                             0,                                                             0,                                                             1;

}


void Animation::construct__RT_3x4__RT_4x4__basedOn__R_T(        int modelID, int fr        )
{
  //int NoOfFrames = modelSet.models[modelID].totalSkeletonFrames;
    int NoOfBones  = modelSet.models[modelID].totalBones;

    for (int b=0; b<NoOfBones; b++)
    {
        construct__RT_3x4__RT_4x4__basedOn__R_T__1bone( modelID, fr, b );
    }
}


void Animation::construct__RT_3x4__R_T__basedOn__RT_4x4(        int modelID, int fr        )
{
  //int NoOfFrames = modelSet.models[modelID].totalSkeletonFrames;
    int NoOfBones  = modelSet.models[modelID].totalBones;

    for (int b=0; b<NoOfBones; b++)
    {
        construct__RT_3x4__R_T__basedOn__RT_4x4__1bone( modelID, fr, b );
    }
}


void Animation::construct__RT_3x4__R_T__basedOn__RT_4x4__1bone( int modelID, int fr, int b )
{

    movingModels[modelID].motionFrames[fr].bones[b].RT_3x4 << movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,2),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,3);


    movingModels[modelID].motionFrames[fr].bones[b].R <<      movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,2),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,2),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,0),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,1),   movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,2);

    movingModels[modelID].motionFrames[fr].bones[b].T <<      movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(0,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(1,3),
                                                              movingModels[modelID].motionFrames[fr].bones[b].RT_4x4(2,3);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

