////Mutiple tracking bang KCF/MIL

//#include <opencv2/core/utility.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//#include "video/background_segm.hpp"
//#include <iostream>
//#include <cstring>
//#include <ctime>
//
//using namespace std;
//using namespace cv;
//
//
//Mat frame;
//Mat fgMaskMOG2;
//Ptr<BackgroundSubtractor> pMOG2;
//int keyboard;
//unsigned int type = CV_32F;
//
//int main(int argc, char** argv) {
//	std::string trackingAlg = "KCF";
//	MultiTracker trackers(trackingAlg);
//
//	std::string videoFileName = "Video_test5.avi";
//	VideoCapture capture(videoFileName);
//	if (!capture.isOpened()) {
//		cerr << "Unable to open video file: " << videoFileName << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	pMOG2 = createBackgroundSubtractorMOG2(500, 10, false);
//
//	while ((char)keyboard != 'q' && (char)keyboard != 27)
//	{
//		if (!capture.read(frame)) {
//			cerr << "Unable to read next frame." << endl;
//			cerr << "Exiting..." << endl;
//			exit(EXIT_FAILURE);
//		}
//		pMOG2->apply(frame, fgMaskMOG2);
//		imshow("FG Mask MOG 2 non filter", fgMaskMOG2);
//
//		Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(1, 1));
//		medianBlur(fgMaskMOG2, fgMaskMOG2, 5);
//		//co anh
//		erode(fgMaskMOG2, fgMaskMOG2, element, Point(-1, -1), 3);
//		//dan anh
//		dilate(fgMaskMOG2, fgMaskMOG2, element, Point(-1, -1), 3);
//		imshow("FG Mask MOG 2", fgMaskMOG2);
//
//		vector<vector<cv::Point> > contours;
//		cv::findContours(fgMaskMOG2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//
//		vector<vector<cv::Point> > objects;
//		vector<cv::Rect2d> objectsBox;
//
//		for (size_t i = 0; i < contours.size(); i++)
//		{
//			cv::Rect2d bBox;
//			bBox = cv::boundingRect(contours[i]);
//
//			if (bBox.area() >= 5000 && bBox.area() < 50000)
//			{
//				objects.push_back(contours[i]);
//				objectsBox.push_back(bBox);
//			}
//		}
//
//		cout << "objects found:" << objectsBox.size() << endl;
//		
//
//		if (trackers.objects.size() == 0 ) {
//			if(objectsBox.size() != 0)
//				trackers.add(frame, objectsBox);
//		}
//		else {
//			for (int i = 0; i < trackers.objects.size(); i++) {
//				int check = 0;
//				cv::Rect2d tmpRect;
//				for (int j = 0; j < objectsBox.size(); j++) {
//					if ((objectsBox[j] & trackers.objects[i]).area() > 1000) {
//						tmpRect = objectsBox[j];
//						check = 1;
//						break;
//					}
//				}
//				if (check != 0)
//					objectsBox.erase(std::remove(objectsBox.begin(), objectsBox.end(), tmpRect), objectsBox.end());
//			}
//
//			for (int i = 0; i < objectsBox.size(); i++) {
//				trackers.add(frame, objectsBox[i]);
//			}
//
//			trackers.update(frame);
//			for (unsigned i = 0; i < trackers.objects.size(); i++)
//				rectangle(frame, trackers.objects[i], Scalar(255, 0, 0), 2, 1);
//		}
//
//		imshow("tracker", frame);
//		keyboard = cv::waitKey(1);
//	}
//	capture.release();
//	destroyAllWindows();
//	return EXIT_SUCCESS;
//}