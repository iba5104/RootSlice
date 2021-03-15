#include "rsSourceCorticalVisual.h"

void rsSourceCorticalVisual::CorticalVisual
( rsSourceCorticalDB *CorticalDB,
  vtkSmartPointer<vtkRenderer> renL )
{  /// declare iterator;
   map<int, vector< vector<double> > >::iterator itMap;
   vector< vector<double> >::iterator itVec2;
   vector<double>::iterator           itVec1;
   /// declare int;
   int iRingNum;
   int i;
   int sliceTempNum;
//   int CorticalCellNum = 0;
//   ofstream fout("staticNum.txt",ios::app);

   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
   vtkSmartPointer<vtkAppendPolyData> append =
      vtkSmartPointer<vtkAppendPolyData>::New();
   vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
   writer->SetFileName( CorticalDB -> CorticalXMLVtpFileName );

   for ( iRingNum = 0, itMap = CorticalDB->objectHeightDB.begin();
         itMap != CorticalDB->objectHeightDB.end();
         iRingNum++, itMap++ )
   {  for ( i=0, itVec2 = (*itMap).second.begin(); itVec2 !=  (*itMap).second.end(); i++, itVec2++)
      {  for ( sliceTempNum = 0, itVec1 = (*itVec2).begin();
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
            ( CorticalDB->objectVerticalDB[iRingNum] );

            superEllipsoid->SetYRadius
            (CorticalDB->objectVerticalDB[iRingNum]);//( CorticalDB->circleSegmentLengthDB[iRingNum][i] );

            superEllipsoid->SetZRadius
            ( CorticalDB->objectHeightDB[iRingNum][i][sliceTempNum] );

            superEllipsoid->SetN1(0.2);
            superEllipsoid->SetN2(0.8);

            superEllipsoidFunction->SetParametricFunction(superEllipsoid);
            superEllipsoidFunction->SetUResolution( CorticalDB->uResolution );
            superEllipsoidFunction->SetVResolution( CorticalDB->vResolution );
            superEllipsoidFunction->SetWResolution( CorticalDB->wResolution );
            superEllipsoidFunction->Update();

            /// Set Scalars;
            // Extract the polydata
            vtkSmartPointer<vtkPolyData> polydata =
               vtkSmartPointer<vtkPolyData>::New();
            polydata = superEllipsoidFunction->GetOutput();

            //declare vtkVector
            //give it some values 4.5.......4.5
            //polydata->getCellData()->setVector(...)

            int pointNum;
            pointNum = polydata->GetNumberOfPoints();


            vtkFloatArray *scalars = vtkFloatArray::New();
            scalars->SetName("Color");
            int numSequence;

            /// Add scalar to point;
            for (numSequence=0; numSequence<pointNum; numSequence++)
            {  scalars->InsertTuple1
//               ( numSequence, double(sliceTempNum) / 2 );
               ( numSequence, 0 );
            }
            polydata->GetPointData()->SetScalars(scalars);
            scalars->Delete();


            /// Set vtkTranform and vtkTransformPloyDataFilter;
            vtkSmartPointer<vtkTransform> trans =
               vtkSmartPointer<vtkTransform>::New();

            vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
               vtkSmartPointer<vtkTransformPolyDataFilter>::New();

            trans->Translate( CorticalDB->circleXDB[iRingNum][i],
                              CorticalDB->objectZPositionDB[iRingNum][i][sliceTempNum],
                              CorticalDB->circleYDB[iRingNum][i] );
            trans->RotateY( (CorticalDB->circleSegmentRotateAngleDB[iRingNum][i]) );
            trans->RotateX( 90 );

            transFilter->SetInputData( polydata );
            transFilter->SetTransform( trans );

            /// Add transFilter to vtkAppendPolyData pointer everytime;
            append->AddInputConnection( transFilter->GetOutputPort() );

            /// vtkPolyDataMapper and vtkActor;
            polyDataMapper->SetInputConnection( transFilter->GetOutputPort() );
            actor->SetMapper( polyDataMapper );

//            actor->RotateY( (CorticalDB->circleSegmentRotateAngleDB[iRingNum][i]) );
//
//            actor->RotateX( 90 );
//
//            actor->SetPosition( CorticalDB->circleXDB[iRingNum][i],
//                                CorticalDB->objectZPositionDB[iRingNum][i][sliceTempNum],
//                                CorticalDB->circleYDB[iRingNum][i] );

//            actor->GetProperty()->SetColor
//            ( CorticalDB->mapRGB[sliceTempNum*CorticalDB->rgbTime  + CorticalDB->rgbStart][0],
//              CorticalDB->mapRGB[sliceTempNum*CorticalDB->rgbTime  + CorticalDB->rgbStart][1],
//              CorticalDB->mapRGB[sliceTempNum*CorticalDB->rgbTime  + CorticalDB->rgbStart][2] );

            actor->GetProperty()->SetOpacity( CorticalDB->objectOpacity );

            renL->AddActor( actor );
         }
      }
   }
   writer->SetInputConnection(append->GetOutputPort());
   writer->Write();
}

void rsSourceCorticalVisual::VacuoleVisual
( rsSourceCorticalDB *CorticalDB,
  vtkSmartPointer<vtkRenderer> renL )
{  /// declare iterator;
   map<int, vector< vector<double> > >::iterator itMap;
   vector< vector<double> >::iterator itVec2;
   vector<double>::iterator           itVec1;
   /// declare int;
   int iRingNum;
   int i;
   int sliceTempNum;

   /// Create vtkAppendPolyData and vtkXMLPolyDataWriter pointer outside the loop;
   vtkSmartPointer<vtkAppendPolyData> append =
      vtkSmartPointer<vtkAppendPolyData>::New();
   vtkSmartPointer<vtkXMLPolyDataWriter> writer =
      vtkSmartPointer<vtkXMLPolyDataWriter>::New();
   writer->SetFileName( CorticalDB -> CorticalVacuoleXMLVtpFileName );

   for ( iRingNum = 0, itMap = CorticalDB->vacuoleHeightDB.begin();
         itMap != CorticalDB->vacuoleHeightDB.end();
         iRingNum++, itMap++ )
   {  for ( i=0, itVec2 = (*itMap).second.begin(); itVec2 !=  (*itMap).second.end(); i++, itVec2++)
      {  for ( sliceTempNum = 0, itVec1 = (*itVec2).begin();
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
            ( CorticalDB->vacuoleVerticalDB[iRingNum] );

            superEllipsoid->SetYRadius
            ( CorticalDB->vacuoleParallelDB[iRingNum][i] );

            superEllipsoid->SetZRadius
            ( CorticalDB->vacuoleHeightDB[iRingNum][i][sliceTempNum] );

            superEllipsoid->SetN1(0.2);
            superEllipsoid->SetN2(0.8);

            superEllipsoidFunction->SetParametricFunction(superEllipsoid);
            superEllipsoidFunction->SetUResolution( CorticalDB->uResolution );
            superEllipsoidFunction->SetVResolution( CorticalDB->vResolution );
            superEllipsoidFunction->SetWResolution( CorticalDB->wResolution );

            /// You need to update() if you want to output the data of object;
            superEllipsoidFunction->Update();

            /// Set Scalars;
            // Extract the polydata
            vtkSmartPointer<vtkPolyData> polydata =
               vtkSmartPointer<vtkPolyData>::New();
            polydata = superEllipsoidFunction->GetOutput();

            int pointNum, cellNum;
            pointNum = polydata->GetNumberOfPoints();
            cellNum = polydata->GetNumberOfCells();

            vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
            scalars->SetName("Color");
            int numSequence;

            /// Add scalar to point;
            for (numSequence=0; numSequence<pointNum; numSequence++)
            {  scalars->InsertTuple1
//               ( numSequence, double(sliceTempNum) / 4 );
               ( numSequence, 0.05 );
            }
            polydata->GetPointData()->SetScalars(scalars);


            /// Set vtkTranform and vtkTransformPloyDataFilter;
            vtkSmartPointer<vtkTransform> trans =
               vtkSmartPointer<vtkTransform>::New();

            vtkSmartPointer<vtkTransformPolyDataFilter> transFilter =
               vtkSmartPointer<vtkTransformPolyDataFilter>::New();

            trans->Translate( CorticalDB->circleXDB[iRingNum][i],
                              CorticalDB->objectZPositionDB[iRingNum][i][sliceTempNum],
                              CorticalDB->circleYDB[iRingNum][i] );
            trans->RotateY( (CorticalDB->circleSegmentRotateAngleDB[iRingNum][i]) );
            trans->RotateX( 90 );

            transFilter->SetInputData( polydata );
            transFilter->SetTransform( trans );

            /// Add transFilter to vtkAppendPolyData pointer everytime;
            append->AddInputConnection( transFilter->GetOutputPort() );

            /// vtkPolyDataMapper and vtkActor;
            polyDataMapper->SetInputConnection( transFilter->GetOutputPort() );
            actor->SetMapper( polyDataMapper );

//            actor->RotateY( (CorticalDB->circleSegmentRotateAngleDB[iRingNum][i]) );
//
//            actor->RotateX( 90 );
//
//            actor->SetPosition( CorticalDB->circleXDB[iRingNum][i],
//                                CorticalDB->objectZPositionDB[iRingNum][i][sliceTempNum],
//                                CorticalDB->circleYDB[iRingNum][i] );
//
//            actor->GetProperty()->SetColor
//            ( CorticalDB->mapRGB[(sliceTempNum)*CorticalDB->rgbTime + 1 + CorticalDB->rgbStart][0],
//              CorticalDB->mapRGB[(sliceTempNum)*CorticalDB->rgbTime + 1 + CorticalDB->rgbStart][1],
//              CorticalDB->mapRGB[(sliceTempNum)*CorticalDB->rgbTime + 1 + CorticalDB->rgbStart][2] );

            actor->GetProperty()->SetOpacity( CorticalDB->vacuoleOpacity );

            renL->AddActor( actor );
         }
      }
   }
   writer->SetInputConnection(append->GetOutputPort());
   writer->Write();
}
