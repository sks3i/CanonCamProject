CanonCam Project

Coded by: Sabarish Kuduwa Sivanath
Contact: saba_rish91@hotmail.com
_______________________________________________________________

Simple program to take picture and record video remotely using a Canon DSLR.

Prerequistes:
_____________
1. EDSDK
	You need to request from Canon's website. (I can't distrubute it)


Usuage:
_______
1. Unzip EDSDK.
2. Make sure headear files and .lib files are visible to the program.
3. Add .dll files to the main directory (Debug folder if you are using VS)


Available functions:
____________________
1. EdsError getCamera(EdsCameraRef *camera);
	To get the camera object
2. EdsError startLiveView(EdsCameraRef camera);
	To start Live View on the camera
3. EdsError startRecording(EdsCameraRef camera);
	To start video recording
4. EdsError stopRecording(EdsCameraRef camera);
	To stop video recording
5. EdsError setCameraAsDestination(EdsCameraRef camera);
	To set camera's SD card the destination
6. EdsError takePicture(EdsCameraRef camera);
	To capture photo