#include "ApplicationManager.h"
#include "Actions\LoadAction.h"
#include "Actions\PlayAction.h"
#include "Figures\CCircle.h"
string PlayAction::FigureType = "";
color  PlayAction::FigureFillClr = WHITE;
int main()
{

	ActionType ActType;
	ApplicationManager AppManager;


	int count = 0;
	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);

	return 0;
}