#include <irrlicht.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>


/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
int main(int p_argCount, char** argArray)
{
	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();

	device->setWindowCaption(L"Cubes");

	// Add a camera
	sceneManager->addCameraSceneNode(NULL, irr::core::vector3df(100, 100, 200), irr::core::vector3df(0, 0, 0));

	// Lets add some cubes for fun
	irr::scene::ISceneNode* cube1 = sceneManager->addCubeSceneNode(50, 0, 2, irr::core::vector3df(0, 0, 0));
	irr::video::ITexture* texture = driver->getTexture("test.jpg");
	cube1->setMaterialTexture(0, texture);
	cube1->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	// Camera capture
	//irr::video::ITexture* texFront = driver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "front");
	irr::video::ITexture* texBackground = driver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "cam");
	//CvCapture* front = cvCreateCameraCapture(0);
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
	//IplImage* face = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);
	IplImage* cam = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);
	IplImage* gray = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);

	while (device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

		//IplImage* fface = cvQueryFrame(front);
		//cvSmooth(fface, fface, CV_GAUSSIAN, 3, 3);
		IplImage* frame = cvQueryFrame(capture);

		if (frame != NULL)
		{
			cvSmooth(frame, frame, CV_GAUSSIAN, 3, 3);

			// Background capture
			//cvCvtColor(fface, face, CV_BGR2BGRA);
			//memcpy(static_cast<char*>(texFront->lock()), face->imageData, face->imageSize);
			//texFront->unlock();

			cvCvtColor(frame, cam, CV_BGR2BGRA);
			memcpy(static_cast<char*>(texBackground->lock()), cam->imageData, cam->imageSize);
			texBackground->unlock();
			driver->draw2DImage(texBackground, irr::core::vector2d<irr::s32>(0, 0));

			// Grayscale for analizes
			cvCvtColor(frame, gray, CV_BGR2GRAY);
			cvThreshold(gray, gray, 128, 255, CV_THRESH_BINARY);
			//cvShowImage("gray", gray);

			CvSeq* contours;
			CvSeq* result;
			CvMemStorage *storage = cvCreateMemStorage(0);

			cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

			//iterating through each contour
			while (contours)
			{
				//obtain a sequence of points of contour, pointed by the variable 'contour'
				result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

				//if there are 4 vertices in the contour(It should be a quadrilateral)
				if (result->total == 4)
				{
					//iterating through each point
					CvPoint *pt[4];
					for (int i = 0; i < 4; i++){
						pt[i] = (CvPoint*) cvGetSeqElem(result, i);
					}

					//driver->draw2DImage(texFront, irr::core::rect<irr::s32>(pt[0]->x, pt[0]->y, pt[2]->x, pt[2]->y), irr::core::rect<irr::s32>(0, 0, 640, 480));

					driver->draw2DLine(irr::core::vector2d<irr::s32>(pt[0]->x, pt[0]->y), irr::core::vector2d<irr::s32>(pt[1]->x, pt[1]->y), irr::video::SColor(255, 255, 0, 0));
					driver->draw2DLine(irr::core::vector2d<irr::s32>(pt[1]->x, pt[1]->y), irr::core::vector2d<irr::s32>(pt[2]->x, pt[2]->y), irr::video::SColor(255, 255, 0, 0));
					driver->draw2DLine(irr::core::vector2d<irr::s32>(pt[2]->x, pt[2]->y), irr::core::vector2d<irr::s32>(pt[3]->x, pt[3]->y), irr::video::SColor(255, 255, 0, 0));
					driver->draw2DLine(irr::core::vector2d<irr::s32>(pt[3]->x, pt[3]->y), irr::core::vector2d<irr::s32>(pt[0]->x, pt[0]->y), irr::video::SColor(255, 255, 0, 0));
				}

				//obtain the next contour
				contours = contours->h_next;
			}
		}


		sceneManager->drawAll();
		driver->endScene();
	}

	//cvReleaseCapture(&front);
	cvReleaseCapture(&capture);
	device->drop();
	return 0;
}