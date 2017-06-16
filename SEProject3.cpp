#include <stdlib.h> 
#include <stdio.h>
#include <math.h>

//structure of balloons
typedef struct ball
{
	double x;    //position x of the ball
	double y;	//position y of the ball
	double z;    //position z of the ball
	double r;	//radius
}Ball;

//the linked list to store the balloons
typedef struct ballList
{
	struct ballList * next;          //to the next balloon
	Ball ball;					  //the balloon
}BallList;

//functions
void insert(Ball ball);				//insert new balloon
double distance(Ball b1, Ball b2);      //judge the distance
double abs(double num);				//get absolute value
int judge(Ball b);					//judge the rationality
void putBall();						//change the beginning position
void putPoint(double x, double y, double z);	//put new point

//parameters
BallList *head = NULL;
double step = 0.02;						//smallest unit to change the position
int num = 0;                                //number of balloons
double sumr = 0;							//sum of r^2

int main()
{
	int n, pointNum, i;
	printf("Number of balloons: ");
	scanf_s("%d", &n);
	printf("Number of points: ");
	scanf_s("%d", &pointNum);
	for (i = 0; i < pointNum; i++)
	{
		printf("No.%d point's position(x,y,z)£º", i + 1);
		double x, y, z;
		scanf_s("%lf %lf %lf", &x, &y, &z);
		putPoint(x, y, z);
	}
	printf("\nNo.\t x\t y\t z\t radius\t sum of r^2\n");
	for (i = 0; i < n; i++)
	{
		putBall();
	}
	printf("\nsum of r^2:\t %lf\n", sumr);
	system("pause");
	return 0;
}

void putPoint(double x, double y, double z)
{
	Ball ball = { x, y, z, 0 };
	insert(ball);
}

void insert(Ball ball)
{
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

void putBall()
{
	Ball ball = { -1 + step, -1 + step, -1 + step, 0 };
	Ball maxBall = ball;
	int i, j, k;
	for (i = 0; ball.x < 1; ++i)
	{
		ball.x += step;
		ball.y = -1 + step;
		ball.z = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;
			ball.z = -1 + step;
			for (k = 0; ball.z < 1; ++k)
			{
				ball.z += step;
				ball.r = 0;
				double rstep = 0.1;
				while (rstep > 0.00001)
				{
					if (ball.r > maxBall.r)
					{
						maxBall = ball;
					}
					ball.r += rstep;
					if (!judge(ball))
					{
						ball.r -= rstep;
						rstep /= 10;
					}
				}
			}
		}
	}
	if (judge(maxBall))
	{
		insert(maxBall);
		num++;
		sumr += maxBall.r * maxBall.r;
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.z, maxBall.r, sumr);
	}
}

int judge(Ball b)
{
	if ((abs(b.x) + b.r) > 1 || (abs(b.y) + b.r) > 1 || (abs(b.z) + b.r>1))
	{
		return false;
	}
	ballList *tmp = head;
	while (tmp)
	{
		Ball ball = tmp->ball;
		if (distance(b, ball) < b.r + ball.r)
		{
			return false;
		}
		tmp = tmp->next;
	}
	return true;
}

double distance(Ball b1, Ball b2)
{
	double x1 = b1.x;
	double y1 = b1.y;
	double z1 = b1.z;
	double x2 = b2.x;
	double y2 = b2.y;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2)*(z1 - z2), 0.5);
}
