// TestCl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestCl.h"
#include "InterfaceObj.h"
#include "HidMgr.h"

#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

extern int gain_mode;			// todo: move to member variable
extern float int_time;				// integration time
extern int frame_size;				// 0: 12x12 frame; 1: 24x24 frame

CInterfaceObject theInterfaceObject;

void print_data();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			bool DeviceFound = FindTheHID();

			string cmd;
			int res = 1;
			int chan = 1;

			if(DeviceFound) {

	//			int e = theInterfaceObject.LoadTrimFile();

				if(true) {
		//			theInterfaceObject.ReadTrimData();
		//			theInterfaceObject.ResetTrim();				// Always do this after loading trim file.

					theInterfaceObject.SelSensor(1);
					theInterfaceObject.SetIntTime(1);			// 1ms
					theInterfaceObject.SetGainMode(0);			// high gain mode

					theInterfaceObject.SelSensor(2);
					theInterfaceObject.SetIntTime(1);			// 1ms
					theInterfaceObject.SetGainMode(0);			// high gain mode

					theInterfaceObject.SelSensor(3);
					theInterfaceObject.SetIntTime(1);			// 1ms
					theInterfaceObject.SetGainMode(0);			// high gain mode

					theInterfaceObject.SelSensor(4);
					theInterfaceObject.SetIntTime(1);			// 1ms
					theInterfaceObject.SetGainMode(0);			// high gain mode

					theInterfaceObject.SelSensor(chan);					
				}
				else { 
					cout << "Trim data not found" << endl;
				}
			}
			else {
				cout << "Device not found" << endl;
			}

			cout << "allowable commands are: selchan, get, setinttime, setgain, reset, exit..." << endl;
			cout << ">";
		
			while (res != 0)
			{
				cin >> cmd;
				// cout << cmd << endl;

				int c = cmd.compare("selchan");

				if (c == 0) {
					cout << "chan: ";
					cin >> chan;
					theInterfaceObject.SelSensor(chan);
				}

				c = cmd.compare("get");

				if (c == 0) {
					theInterfaceObject.CaptureFrame12(chan);
					print_data();
				}

				c = cmd.compare("getcorr");

				if (c == 0) {
					theInterfaceObject.GetCorrected(chan);
					// print_data();
				}

				c = cmd.compare("setinttime");

				if (c == 0) {
					int itime;
					cout << "int time: ";
					cin >> itime;
					theInterfaceObject.SetIntTime((float)itime);
				}

				c = cmd.compare("setgain");

				if (c == 0) {
					int gain;
					cout << "gain (0-high, 1-low): " << endl;
					cin >> gain;
					theInterfaceObject.SetGainMode(gain);
				}

				c = cmd.compare("reset");

				if (c == 0) {
					bool found;
					found = FindTheHID();
					if(found) cout << "Device found" << endl;
					else cout << "Device not found" << endl;
				}

				c = cmd.compare("resettrim");

				if (c == 0) {
					theInterfaceObject.ReadTrimData();
					theInterfaceObject.ResetTrim();				// Always do this after loading trim file.
				}

				cout << ">";
				res = cmd.compare("exit");
			}

			cout << "Press any key and then return to end..." << endl;
			cin.get();
		}
	}
	else
	{
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

void print_data()
{
	int dim;

	if (frame_size) dim = 24;
	else dim = 12;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			cout << theInterfaceObject.frame_data[i][j] << " ";
		}
		cout << endl;
	}
}
