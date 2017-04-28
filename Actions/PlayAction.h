#pragma once

#include"Action.h"
#include"..\Figures\CFigure.h"
#include<queue>

class PlayAction : public Action
{
private:
	
	color FigureDrawClr;
	static color FigureFillClr;
	priority_queue<int>FigureAreas;
	Input* pIn; Output* pOut;
	static string FigureType;
public:
	void SetSubActionForColor();
	PlayAction(ApplicationManager* pApp);
	void SetSubActionForFigureType();
	//Get action parameters function
	virtual bool ReadActionParameters();

	//Execute the action
	virtual void Execute();

	//A function to check the figure type
	static bool CheckFigureType(CFigure* ptr);

	//A function to check the figure draw color
	bool CheckFigureDrawClr(CFigure* ptr);

	//A function to check the figure fill color
	bool CheckFigureFillClr(CFigure* ptr);

	//A function to claculate and queue figure areas
	void CalcAndQueueAreas();
	void PlayColorTypeGame();
	void PlayFigTypeGame();
	int GetNumOfColorfulFigures();
	static bool CheckColorType(CFigure* ptr);
	int GetNumOfFigure();
};
