#define _USE_MATH_DEFINES
#include <cmath> 
#include "rsMXCoreVisual.h"

// Store the objects of each ring into the different vectors;
//
void rsMXCoreVisual::MXVisual
(   rsMXBoundaryOutDB *RsMXBoundaryOutDB,
    vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
   map<int, vector< vector <vector<double> > > >::iterator itMap;
   vector< vector <vector<double> > >::iterator itVec3;
   vector< vector<double> >::iterator itVec2;
   vector<double>::iterator itVec1;
   /// declare int;
   int i;
   int iRingNum;
   int cellNum;
   int sliceTempNum;
   int MXCoreNum = 0;

   ofstream fout("staticNum.txt",ios::app);

   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
   vtkSmartPointer<vtkAppendPolyData> append =
      vtkSmartPointer<vtkAppendPolyData>::New();
   vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
   writer->SetFileName("MXCore.vtp");

   /// cout << circleSegmentLengthDB;
   for ( itMap = RsMXBoundaryOutDB->xylemOutRingObjectHeightDB.begin(), i = 0;
         itMap != RsMXBoundaryOutDB->xylemOutRingObjectHeightDB.end();
         itMap++, i++ )
   {  for ( itVec3 = (*itMap).second.begin(), iRingNum = 0;
            itVec3!=(*itMap).second.end();
            itVec3++, iRingNum++ )
      {  for ( itVec2 = (*itVec3).begin(), cellNum = 0;
               itVec2!=(*itVec3).end();
               itVec2++, cellNum++ )
            for ( sliceTempNum = 0, itVec1 = (*itVec2).begin();
                  itVec1 !=  (*itVec2).end();
                  sliceTempNum++, itVec1++ )
            {  vtkSmartPointer<vtkParametricSuperEllipsoid> superEllipsoid
               = vtkSmartPointer<vtkParametricSuperEllipsoid>::New();

               vtkSmartPointer<vtkParametricFunctionSource> superEllipsoidFunction
               = vtkSmartPointer<vtkParametricFunctionSource>::New();

               vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
               = vtkSmartPointer<vtkPolyDataMapper>::New();

               vtkSmartPointer<vtkActor> actor
               = vtkSmartPointer<vtkActor>::New();

               superEllipsoid->SetXRadius
               ( RsMXBoundaryOutDB->xylemOutRingObjectVerticalDB[i][iRingNum] );

               superEllipsoid->SetYRadius
               ( RsMXBoundaryOutDB->xylemOutRingCircleSegmentLengthDB[i][iRingNum][cellNum] );

               superEllipsoid->SetZRadius
               ( RsMXBoundaryOutDB->xylemOutRingObjectHeightDB[i][iRingNum][cellNum][sliceTempNum] );

               superEllipsoid->SetN1( 0.2 );
               superEllipsoid->SetN2( 0.8 );

               superEllipsoidFunction->SetParametricFunction( superEllipsoid );
               superEllipsoidFunction->SetUResolution( RsMXBoundaryOutDB->uResolution );
               superEllipsoidFunction->SetVResolution( RsMXBoundaryOutDB->vResolution );
               superEllipsoidFunction->SetWResolution( RsMXBoundaryOutDB->wResolution );

               /// You need to update() if you want to output the data of object;
               superEllipsoidFunction->Update();

               /// Set Scalars;
               // Extract the polydata
               vtkSmartPointer<vtkPolyData> polydata =
                  vtkSmartPointer<vtkPolyData>::New();
               polydata = superEllipsoidFunction->GetOutput();

               int pointNum;
               pointNum = polydata->GetNumberOfPoints();

               vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
               scalars->SetName("Color");
               int numSequence;

               /// Add scalar to point;
               for (numSequence=0; numSequence<pointNum; numSequence++)
               {  scalars->InsertTuple1
//                  ( numSequence, double(sliceTempNum) / 5 );
                  ( numSequence, 0.0369004 );

               }
               polydata->GetPointData()->SetScalars(scalars);


               /// Set vtkTranform and vtkTransformPloyDataFilter;
               vtkSmartPointer<vtkTransform> trans =
                  vtkSmartPointer<vtkTransform>::New();

               vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
                  vtkSmartPointer<vtkTransformPolyDataFilter>::New();

               trans->Translate( RsMXBoundaryOutDB->xylemOutRingCircleXDB[i][iRingNum][cellNum],
                                 RsMXBoundaryOutDB->xylemOutRingObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
                                 RsMXBoundaryOutDB->xylemOutRingCircleYDB[i][iRingNum][cellNum] );
               trans->RotateY( RsMXBoundaryOutDB->xylemOutRingCircleSegmentRotateAngleDB[i][iRingNum][cellNum] );
               trans->RotateX( 90 );

               transFilter->SetInputData( polydata );
               transFilter->SetTransform( trans );

               /// Add transFilter to vtkAppendPolyData pointer everytime;
               append->AddInputConnection( transFilter->GetOutputPort() );

               /// vtkPolyDataMapper and vtkActor;
               polyDataMapper->SetInputConnection( transFilter->GetOutputPort() );
               actor->SetMapper( polyDataMapper );

//               polyDataMapper->SetInputConnection
//               ( superEllipsoidFunction->GetOutputPort() );
//
//               actor->SetMapper( polyDataMapper );
//
//               actor->RotateY
//               ( (RsMXBoundaryOutDB->xylemOutRingCircleSegmentRotateAngleDB[i][iRingNum][cellNum]) );
//
//               actor->RotateX( 90 );
//
//               actor->SetPosition
//               ( RsMXBoundaryOutDB->xylemOutRingCircleXDB[i][iRingNum][cellNum],
//                 RsMXBoundaryOutDB->xylemOutRingObjectZPositionDB[i][iRingNum][cellNum][sliceTempNum],
//                 RsMXBoundaryOutDB->xylemOutRingCircleYDB[i][iRingNum][cellNum] );
//
//               actor->GetProperty()->SetColor
//               ( RsMXBoundaryOutDB->mapRGB[sliceTempNum * RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum * RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
//                 RsMXBoundaryOutDB->mapRGB[sliceTempNum * RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
//               actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

               renL->AddActor( actor );
               //cout << "rsMXCoreVisual - actor: " << actor << endl;
               MXCoreNum += 1;
            }
      }
   }
   fout << "MXCoreNum: " << MXCoreNum << endl;
   writer->SetInputConnection(append->GetOutputPort());
   writer->Write();
}



void rsMXCoreVisual::MXCenterRingVisual
(   rsMXBoundaryOutDB *RsMXBoundaryOutDB,
    vtkSmartPointer<vtkRenderer> renL
)
{  /// declare iterator;
   map<int, vector<double> >::iterator itMap;
   vector<double>::iterator itVec1;
   /// declare int;
   int i;
   int sliceTempNum;

   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
   vtkSmartPointer<vtkAppendPolyData> append =
      vtkSmartPointer<vtkAppendPolyData>::New();
   vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
   writer->SetFileName("MXCenterRing.vtp");

   for ( itMap = RsMXBoundaryOutDB->xylemCenterRingObjectHeightDB.begin(), i = 0;
         itMap != RsMXBoundaryOutDB->xylemCenterRingObjectHeightDB.end();
         itMap++, i++ )
   {  for ( sliceTempNum = 0, itVec1 = (*itMap).second.begin();
            itVec1 !=  (*itMap).second.end();
            sliceTempNum++, itVec1++ )
      {  vtkSmartPointer<vtkCylinderSource> cylinder
         = vtkSmartPointer<vtkCylinderSource>::New();

         vtkSmartPointer<vtkPolyDataMapper> polyDataMapper
         = vtkSmartPointer<vtkPolyDataMapper>::New();

         vtkSmartPointer<vtkActor> actor
         = vtkSmartPointer<vtkActor>::New();

         cylinder->SetCenter
         ( RsMXBoundaryOutDB-> centerX[i],
           RsMXBoundaryOutDB-> xylemCenterRingObjectZPositionDB[i][sliceTempNum],
           RsMXBoundaryOutDB-> centerY[i] );

         cylinder->SetRadius( RsMXBoundaryOutDB->eachRingRadius[i] );
         cylinder->SetHeight( RsMXBoundaryOutDB->xylemCenterRingObjectHeightDB[i][sliceTempNum] );
         cylinder->SetResolution(20);
         cylinder->SetCapping( 0 );

         /// You need to update() if you want to output the data of object;
         cylinder->Update();

         /// Set Scalars;
         // Extract the polydata
         vtkSmartPointer<vtkPolyData> polydata =
            vtkSmartPointer<vtkPolyData>::New();
         polydata = cylinder->GetOutput();

         int pointNum, cellNum;
         pointNum = polydata->GetNumberOfPoints();
         cellNum = polydata->GetNumberOfCells();

         vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
         scalars->SetName("Color");
         int numSequence;

         /// Add scalar to point;
         for (numSequence=0; numSequence<pointNum; numSequence++)
         {  scalars->InsertTuple1
          ( numSequence, 0.252768 );
//            ( numSequence, double(sliceTempNum) / 4 );
         }
         polydata->GetPointData()->SetScalars( scalars );

         /// Add polydata to vtkAppendPolyData pointer everytime;
         append->AddInputData( polydata );

         /// vtkPolyDataMapper and vtkActor;
         polyDataMapper->SetInputData( polydata );
         actor->SetMapper( polyDataMapper );

//         polyDataMapper->SetInputConnection
//         ( cylinder->GetOutputPort() );
//
//         actor->SetMapper( polyDataMapper );
//
//         actor->GetProperty()->SetColor
//         ( RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][0],
//           RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][1],
//           RsMXBoundaryOutDB->mapRGB[sliceTempNum*RsMXBoundaryOutDB->rgbTime + RsMXBoundaryOutDB->rgbStart][2] );
//         actor->GetProperty()->SetOpacity( RsMXBoundaryOutDB -> objectOpacity );

         renL->AddActor( actor );
      }
   }
      writer->SetInputConnection(append->GetOutputPort());
   writer->Write();
}

