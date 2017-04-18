#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddTriangleAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	/*We get the user actions, we define two main types of actions,
	(1) a simple action, that's an action taken directly from an on-screen icon
	(2) a nested action, that's an action taken from a sub menu
	-for action number 1, we simple return the action type to the main
	-for action number 2, we do the following: 
	   [1] show the sub menu
	   [2] wait for the user to click an icon from the sub menu
	   [3] hide th sub menu(that includes a click in the sub menu or outside it)
	   [4] return the selected action to the main function*/

	//Ask the input to get the action from the user.
	ActionType Type = pIn->GetUserAction(), ret;

	switch (Type) {
    
	case MODE_DRAW_SUB_MENU1_Clicked:   //figures
		pOut->CreateDrawToolBarUp(1, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(figure option)
		pOut->CreateDrawToolBarUp(1, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU2_Clicked:  //pens
		pOut->CreateDrawToolBarUp(2, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(pen option)
		pOut->CreateDrawToolBarUp(2, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU3_Clicked: //brushes
		pOut->CreateDrawToolBarUp(3, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(brushes option)
		pOut->CreateDrawToolBarUp(3, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU4_Clicked:  //background colors
		pOut->CreateDrawToolBarUp(4, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(background colors option)
		pOut->CreateDrawToolBarUp(4, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU5_Clicked:  //border width
		pOut->CreateDrawToolBarUp(5, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(border width option)
		pOut->CreateDrawToolBarUp(5, true);  //hide sub menu
		return ret; 

	case ITM_RESIZE_Clicked:  //resize options
		pOut->CreateDrawToolBarUp(6, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(resize option)
		pOut->CreateDrawToolBarUp(6, true);  //hide sub menu
		return ret;
	}

	return Type;  //if not a sub menu action, return it directly.
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);
			break;

		case DRAW_CIRC:
			pAct = new AddCircleAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriangleAction(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
