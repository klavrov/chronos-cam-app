/****************************************************************************
 *  Copyright (C) 2013-2017 Kron Technologies Inc <http://www.krontech.ca>. *
 *                                                                          *
 *  This program is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  (at your option) any later version.                                     *
 *                                                                          *
 *  This program is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include <pthread.h>
#include <semaphore.h>
#include <QProgressDialog>

#include "errorCodes.h"
#include "defines.h"

#include "video.h"
#include "control.h"
#include "userInterface.h"
#include "string.h"
#include "types.h"

#define RECORD_LENGTH_MIN       1           //Minimum number of frames in the record region
#define SEGMENT_COUNT_MAX       (32*1024)   //Maximum number of record segments in segmented mode

#define MAX_FRAME_SIZE_H		1920
#define MAX_FRAME_SIZE_V		1080
#define MAX_FRAME_SIZE          (MAX_FRAME_SIZE_H * MAX_FRAME_SIZE_V * 8 / 12)
#define BITS_PER_PIXEL			12
#define BYTES_PER_WORD			32

#define FPN_AVERAGE_FRAMES		16	//Number of frames to average to get FPN correction data

#define SENSOR_DATA_WIDTH		12
#define COLOR_MATRIX_INT_BITS	3

#define FREE_SPACE_MARGIN_MULTIPLIER 1.1    //Drive must have at least this factor more free space than the estimated file size to allow saving

#define TRIGGERDELAY_TIME_RATIO 0
#define TRIGGERDELAY_SECONDS 1
#define TRIGGERDELAY_FRAMES 2

#define FLAG_BATTERY_PRESENT   (1 << 0)
#define FLAG_ADAPTOR_PRESENT   (1 << 1)
#define FLAG_CHARGING          (1 << 2)
#define FLAG_AUTO_POWERON      (1 << 3)
#define FLAG_OVER_TEMP         (1 << 4)
#define FLAG_SHIPPING_MODE     (1 << 5)
#define FLAG_SHUTDOWN_REQUEST  (1 << 6)

typedef struct {
	ImagerSettings_t is;
	bool valid;
	bool hasBeenSaved;
	bool hasBeenViewed;
	UInt32 ignoreSegments;
} RecordSettings_t;

typedef struct {
	const char *name;
	double matrix[9];
} ColorMatrix_t;

//class Camera
//
class Camera : public QObject {
	Q_OBJECT

public:
	Camera();
	~Camera();
	CameraErrortype init(Video * vinstInst, Control * cinstInst);
	Int32 startRecording(void);
	Int32 stopRecording(void);
	Video * vinst;
	Control * cinst;

	RecordSettings_t recordingData;
	SensorInfo_t     getSensorInfo() { return sensorInfo; }

	bool liveLoopActive = false;
	UInt32 liveLoopTime = 2000;	//in milliseconds

	UInt32 setImagerSettings(ImagerSettings_t settings);
	UInt32 setIntegrationTime(double intTime, FrameGeometry *geometry, Int32 flags);
	bool isValidResolution(FrameGeometry *geometry);
	UInt32 setPlayMode(bool playMode);
	bool focusPeakEnabled;

	void setCCMatrix(const double *matrix);
	void setWhiteBalance(const double *rgb);
	int autoWhiteBalance(unsigned int x, unsigned int y);
	void setFocusAid(bool enable);
	bool getFocusAid();
	int blackCalAllStdRes(bool factory = false, QProgressDialog *dialog = NULL);

	void setBncDriveLevel(UInt32 level);

	bool getFocusPeakEnable(void);
	void setFocusPeakEnable(bool en);
	bool getZebraEnable(void);
	void setZebraEnable(bool en);
	int getUnsavedWarnEnable(void);
	void setUnsavedWarnEnable(int newSetting);
	int getAutoPowerMode(void);
	void setAutoPowerMode(int newSetting);
	bool getFanDisable(void);
	void setFanDisable(bool dis);

	char * getSerialNumber(void) {return serialNumber;}
	void setSerialNumber(const char * sn) {strcpy(serialNumber, sn);}
	bool getIsColor() {return isColor;}

	UInt32 getMaxRecordRegionSizeFrames(FrameGeometry *geometry);

	UInt8 getFocusPeakColorLL(void);
	void setFocusPeakColorLL(UInt8 color);
	void setFocusPeakThresholdLL(UInt32 thresh);
	double convertFocusPeakThreshold(UInt32 thresh);
	UInt32 getFocusPeakThresholdLL(void);
	Int32 readSerialNumber(char * dest);
	Int32 writeSerialNumber(char * src);
	UInt16 getFPGAVersion(void);
	UInt16 getFPGASubVersion(void);
	bool ButtonsOnLeft;
	bool UpsideDownDisplay;

private:
	bool recording;
	bool playbackMode;

	SensorInfo_t sensorInfo;
	bool isColor;

	int focusPeakColorIndex;
	bool zebraEnabled;
	bool fanDisabled;
	char serialNumber[SERIAL_NUMBER_MAX_LEN+1];

	QString fpColors[7] = {"blue", "green", "cyan", "red", "magenta", "yellow", "white"};


public:
	// Actual white balance applied at runtime.
	double whiteBalMatrix[3] = { 1.0, 1.0, 1.0 };
	double colorCalMatrix[9] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	};
	double focusPeakLevel = FOCUS_PEAK_API_MED;

	/* Color Matrix Presets */
	const ColorMatrix_t ccmPresets[2] = {
		{ "CIECAM16/D55", {
			  +1.9147, -0.5768, -0.2342,
			  -0.3056, +1.3895, -0.0969,
			  +0.1272, -0.9531, +1.6492,
		  }
		},
		{ "CIECAM02/D55", {
			  +1.2330, +0.6468, -0.7764,
			  -0.3219, +1.6901, -0.3811,
			  -0.0614, -0.6409, +1.5258,
		  }
		}
	};

	UInt8 getWBIndex();
	void  setWBIndex(UInt8 index);
	int unsavedWarnEnabled;
	int autoPowerMode;
	bool videoHasBeenReviewed;
	bool autoSave;
	int autoSavePercent;
	bool autoSavePercentEnabled;
	bool shippingMode;

	void set_autoSave(bool state);
	bool get_autoSave();

	bool autoRecord;
	void set_autoRecord(bool state);
	bool get_autoRecord();

	bool demoMode;
	void set_demoMode(bool state);
	bool get_demoMode();

	bool getButtonsOnLeft();
	void setButtonsOnLeft(bool en);
	bool getUpsideDownDisplay();
	void setUpsideDownDisplay(bool en);
	bool RotationArgumentIsSet();
	void upsideDownTransform(int rotation);
	void updateVideoPosition();
	int getFocusPeakColor();
	void setFocusPeakColor(int value);

	void on_chkLiveLoop_stateChanged(int arg1);
	void on_spinLiveLoopTime_valueChanged(int arg1);
	int getAutoSavePercent(void);
	void setAutoSavePercent(int newSetting);
	bool getAutoSavePercentEnabled(void);
	void setAutoSavePercentEnabled(bool newSetting);
	bool getShippingMode(void);
	void setShippingMode(int newSetting);

private:
	QString lastState = "idle";
	QTimer * loopTimer;
	bool loopTimerEnabled = false;

protected slots:
	/* Slots from the API on how to handle value changes. */
	void api_state_valueChanged(const QVariant &value);
	void api_wbMatrix_valueChanged(const QVariant &value);
	void api_colorMatrix_valueChanged(const QVariant &value);

	void onLoopTimer();
};

#endif // CAMERA_H
