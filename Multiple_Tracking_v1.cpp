////Version 1 luc bao ve
//
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/videoio.hpp"
//#include <opencv2/highgui.hpp>
//#include <opencv2/video.hpp>
//#include "opencv2/objdetect.hpp"
//#include "video/background_segm.hpp"
//#include "bgsegm.hpp"
//#include <iostream>
//#include <sstream>
//
//typedef struct {
//	cv::KalmanFilter kalmanFilter;
//	cv::Rect objectsBox;
//	int tracking_ID;
//	std::vector<cv::Point> object;
//	cv::MatND r_hist;
//	cv::MatND g_hist;
//	cv::MatND b_hist;
//	//cv::Mat hog;
//} tracking;
//
//using namespace cv;
//using namespace std;
//// Global variables
//
//Mat frame;
//cv::Mat res;
//Mat fgMaskMOG2;
//Ptr<BackgroundSubtractor> pMOG2;
//int keyboard;
//unsigned int type = CV_32F;
//vector<cv::KalmanFilter> vKalmanFilters;
//vector<Point> vmouse, vkalman;
//vector<tracking> tmpvTracking;
//int y = 0;
//
//// Initialize parameters
//int imgCount = 1;
///// Establish the number of bins
//int histSize = 8;
//
///// Set the ranges ( for B,G,R) )
//float range[] = {0, 256};
//const float* histRange = { range };
//
//
//Mat mask = Mat();
//
//void processVideo(char* videoFilename);
//
//int main()
//{
//	namedWindow("FG Mask MOG 2");
//	pMOG2 = createBackgroundSubtractorMOG2(500, 10, true);
//	processVideo("Video_test5.avi");
//
//	destroyAllWindows();
//	return EXIT_SUCCESS;
//}
//
////Mat Hog(Mat image) {
////	vector<float> features;
////	vector<Point> locations;
////	//resize(image, image, Size(64, 128));
////	Mat img;
////	//cvtColor(image, img, CV_RGB2GRAY);
////	HOGDescriptor *HoG = new HOGDescriptor();
////	HoG->compute(image, features, Size(32, 32), Size(0, 0), locations);
////	Mat Hogfeat;
////	Hogfeat.create(features.size(), 1, CV_32FC1);
////	for (int i = 0; i<features.size(); i++) {
////		Hogfeat.at<float>(i, 0) = features.at(i);
////	}
////	return Hogfeat;
////}
//
//void processVideo(char* videoFilename) {
//	VideoCapture capture(videoFilename);
//	if (!capture.isOpened()) {
//		cerr << "Unable to open video file: " << videoFilename << endl;
//		exit(EXIT_FAILURE);
//	}
//
//	//int k = 0;
//
//	while ((char)keyboard != 'q' && (char)keyboard != 27)
//	{
//			//read the current frame
//			if (!capture.read(frame)) {
//				cerr << "Unable to read next frame." << endl;
//				cerr << "Exiting..." << endl;
//				exit(EXIT_FAILURE);
//			}
//
//			
//			cv::Mat b_hist, g_hist, r_hist;
//
//			//update the background model
//			pMOG2->apply(frame, fgMaskMOG2);
//			imshow("FG Mask MOG 2 non filter", fgMaskMOG2);
//
//			Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(1, 1));
//			medianBlur(fgMaskMOG2, fgMaskMOG2, 5);
//			//co ảnh
//			erode(fgMaskMOG2, fgMaskMOG2, element, Point(-1, -1), 3);
//			//dãn ảnh
//			dilate(fgMaskMOG2, fgMaskMOG2, element, Point(-1, -1), 3);
//			imshow("FG Mask MOG 2", fgMaskMOG2);
//
//
//			/*	Mat blur;
//			blur = fgMaskMOG2.clone();
//			Mat element = getStructuringElement(MORPH_CROSS, Size(3,3),Point(1,1));
//			medianBlur(blur, blur,5);
//			erode(blur,blur,element, Point(-1, -1), 3);
//			imshow("Remove Noise", blur);
//			fgMaskMOG2.copyTo(res);
//			fgMaskMOG2 = blur.clone();*/
//
//			vector<vector<cv::Point> > contours;
//			cv::findContours(fgMaskMOG2, contours, CV_RETR_EXTERNAL,
//				CV_CHAIN_APPROX_NONE);
//			// <<<<< Contours detection
//
//			// >>>>> Filtering
//			vector<vector<cv::Point> > objects;
//			vector<cv::Rect> objectsBox;
//			vector<tracking> vTracking;
//
//			for (size_t i = 0; i < contours.size(); i++)
//			{
//				cv::Rect bBox;
//				bBox = cv::boundingRect(contours[i]);
//
//				// Searching for a bBox
//				if (bBox.area() >= 3000 && bBox.area() < 20000)
//				{
//					objects.push_back(contours[i]);
//					objectsBox.push_back(bBox);
//				}
//			}
//			// <<<<< Filtering
//
//			cout << "objects found:" << objectsBox.size() << endl;
//
//			for (size_t t = 0; t < objectsBox.size(); t++)
//			{
//				//k++;
//				//cv::drawContours(frame, objects, t, CV_RGB(20, 150, 20), 1);
//				cv::rectangle(frame, objectsBox[t], CV_RGB(0, 255, 0), 2);
//
//				cv::Point center;
//				center.x = objectsBox[t].x + objectsBox[t].width / 2;
//				center.y = objectsBox[t].y + objectsBox[t].height / 2;
//				//cv::circle(frame, center, 2, CV_RGB(20, 150, 20), -1);
//
//				/*stringstream sstr;
//				sstr << "(" << center.x << "," << center.y << ")";
//				cv::putText(frame, sstr.str(),
//					cv::Point(center.x + 3, center.y - 3),
//					cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(20, 150, 20), 2);*/
//
//				//KalmanFilter KF(stateSize, measSize, contrSize, type);
//				cv::KalmanFilter KF(4, 2, 0, type);
//				//Transition State Matrix F
//				KF.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
//				//Measurement Matrix H
//				Mat_<float> measurement(2, 1); measurement.setTo(Scalar(0));
//				//State
//				KF.statePre.at<float>(0) = center.x;
//				KF.statePre.at<float>(1) = center.y;
//				KF.statePre.at<float>(2) = 0;
//				KF.statePre.at<float>(3) = 0;
//				setIdentity(KF.measurementMatrix);
//				// Process Noise Covariance Matrix Q
//				setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
//				// Measures Noise Covariance Matrix R
//				setIdentity(KF.measurementNoiseCov, Scalar::all(10));
//				setIdentity(KF.errorCovPost, Scalar::all(.1));
//
//				tracking tmpTracking;
//				tmpTracking.tracking_ID = t;
//				tmpTracking.kalmanFilter = KF;
//				tmpTracking.objectsBox = objectsBox[t];
//				tmpTracking.object = objects[t];
//				cv::Mat objFrame;
//				objFrame = frame(objectsBox[t]);
//				//resize(objFrame, objFrame, Size(64, 128));
//				vector<Mat> rgb_planes;
//				split(objFrame, rgb_planes);
//				//cv::cvtColor(objFrame, objFrame, cv::COLOR_HSV2RGB);
//				/// Compute the histograms:
//				calcHist(&rgb_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange);
//				calcHist(&rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange);
//				calcHist(&rgb_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange);
//
//				//normalize(tmpTracking.hist, tmpTracking.hist, 0, 1, NORM_MINMAX, -1, Mat());
//				normalize(b_hist, b_hist, 0, 1, NORM_MINMAX, -1, Mat());
//				normalize(g_hist, g_hist, 0, 1, NORM_MINMAX, -1, Mat());
//				normalize(r_hist, r_hist, 0, 1, NORM_MINMAX, -1, Mat());
//
//				tmpTracking.r_hist = r_hist;
//				tmpTracking.g_hist = g_hist;
//				tmpTracking.b_hist = b_hist;
//				vTracking.push_back(tmpTracking);
//			}
//
//			for (int i = 0; i < vTracking.size(); i++) {
//				int x = 0;
//				if (tmpvTracking.size() == 0) {
//					vTracking[0].tracking_ID = 0;
//					tmpvTracking.push_back(vTracking[0]);
//					break;
//				}
//				double tmpcompareHist = 2.5;
//				double hist = 0;
//				double maxHist = 0;
//				for (int j = 0; j < tmpvTracking.size(); j++) {
//					hist = compareHist(vTracking[i].r_hist, tmpvTracking[j].r_hist, CV_COMP_CORREL) + compareHist(vTracking[i].g_hist, tmpvTracking[j].g_hist, CV_COMP_CORREL) + compareHist(vTracking[i].b_hist, tmpvTracking[j].b_hist, CV_COMP_CORREL);
//					if (hist > maxHist)
//						maxHist = hist;
//					cout << hist << endl;
//					if (hist > tmpcompareHist) {
//						tmpcompareHist = hist;
//						vTracking[i].tracking_ID = tmpvTracking[j].tracking_ID;
//						vTracking[i].kalmanFilter = tmpvTracking[j].kalmanFilter;
//						vTracking[i].r_hist = tmpvTracking[j].r_hist;
//						vTracking[i].g_hist = tmpvTracking[j].g_hist;
//						vTracking[i].b_hist = tmpvTracking[j].b_hist;
//						x = 1;
//						//break;
//					}
//				}
//				if (x != 1 /*&& maxHist < 2.5*/) {
//					y++;
//					vTracking[i].tracking_ID = y;
//					tmpvTracking.push_back(vTracking[i]);
//				}
//			}
//
//
//			// <<<<< Detection result
//			cout << "vTracking:" << vTracking.size() << endl;
//			for (size_t i = 0; i < vTracking.size(); i++) {
//				// First predict, to update the internal statePre variable
//				Mat prediction = vTracking[i].kalmanFilter.predict();
//				Point predictPt(prediction.at<float>(0), prediction.at<float>(1));
//				cv::circle(frame, predictPt, 2, CV_RGB(255, 0, 0), 10);
//
//				Mat_<float> measurement(2, 1);
//				measurement(0) = vTracking[i].objectsBox.x + vTracking[i].objectsBox.width / 2;
//				measurement(1) = vTracking[i].objectsBox.y + vTracking[i].objectsBox.height / 2;
//
//				// The update phase 
//				Mat estimated = vTracking[i].kalmanFilter.correct(measurement);
//				Point statePt(estimated.at<float>(0), estimated.at<float>(1));
//				Point measPt(measurement(0), measurement(1));
//				cv::circle(frame, measPt, 2, CV_RGB(0, 0, 255), 5);
//
//				cv::Point center;
//				center.x = vTracking[i].objectsBox.x + vTracking[i].objectsBox.width / 2;
//				center.y = vTracking[i].objectsBox.y + vTracking[i].objectsBox.height / 2;
//
//				stringstream sstr;
//				sstr << "(" << vTracking[i].tracking_ID << ")";
//				cv::putText(frame, sstr.str(),
//					cv::Point(center.x + 3, center.y - 3),
//					cv::FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255, 255, 255), 2);
//			}
//
//			cout << "tmpvTracking:" << tmpvTracking.size() << endl;
//
//			// Final result
//			cv::imshow("Tracking", frame);
//			// User key
//			keyboard = cv::waitKey(1);
//		
//	}
//	// <<<<< Main loop
//
//	//delete capture object
//	capture.release();
//}
//
