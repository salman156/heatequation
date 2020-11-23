// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject2.h"
#include <GL/glew.h>
#include <cmath>
#include <GLFW/glfw3.h>
#include <thread>
#define MAX_LOADSTRING 100
#define PI 3.14159265358979323846

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND EDITC1;
HWND EDITC2;
HWND EDITALPHA;
HWND EDITA;
HWND EDITB;
HWND EDITT;
HWND EDITTAU;
void Progonka(int n, double* a, double* c, double* b, double* f, double* x);
void GetNextTimeLayer(int curr);
void FindAnswer();
void AddControls(HWND hWnd) {
	CreateWindowW(L"static", L"C1", WS_VISIBLE | WS_CHILD, 100, 32, 50, 20, hWnd, NULL, NULL, NULL);
	EDITC1=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 52, 50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"C2", WS_VISIBLE | WS_CHILD, 150, 32, 50, 20, hWnd, NULL, NULL, NULL);
	EDITC2=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 52, 50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"ALPHA", WS_VISIBLE | WS_CHILD, 200, 32, 50, 20, hWnd, NULL, NULL, NULL);
	EDITALPHA=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 52, 50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"a", WS_VISIBLE | WS_CHILD, 100, 82, 50, 20, hWnd, NULL, NULL, NULL);
	EDITA=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 102, 50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"b", WS_VISIBLE | WS_CHILD, 150, 82, 50, 20, hWnd, NULL, NULL, NULL);
	EDITB=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 102,50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"T", WS_VISIBLE | WS_CHILD, 200, 82, 50, 20, hWnd, NULL, NULL, NULL);
	EDITT=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 102, 50, 30, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Текущее показываемое t", WS_VISIBLE | WS_CHILD, 100, 132, 200, 20, hWnd, NULL, NULL, NULL);
	EDITTAU=CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 152, 50, 30, hWnd, NULL, NULL, NULL);

}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
	
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      400, 200, 300, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
const double E = 2.71828182845904523536;
double C1;
double C2;
double alpha;
double a=1.;
double b=1.;
double T;
int currT;
double uh[11][11][11];
int ready[11] = {0,0,0,0,0,0,0,0,0,0,0};
double hx=.1;
double hy=.1;
double ht;
//
int pressed = 0;
double xpos_offset, ypos_offset;
void mouse_button_rotate(GLFWwindow* window, double xpos, double ypos) {
	if (pressed) {
		glRotatef(2, 0 , 0, xpos-xpos_offset);
		glfwGetCursorPos(window, &xpos_offset, &ypos_offset);
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		glRotatef(1, 1, 0, 0);
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		glRotatef(1, -1, 0, 0);
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		glRotatef(1, 0, 1, 0);
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		glRotatef(1, 0, -1, 0);

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xpos_offset, &ypos_offset);
		pressed = 1;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		pressed = 0;
	}
}
double FindMax(double uh[11][11][11], int curr) {
	double max = uh[curr][0][0];
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			if (uh[curr][j][i] > max)
				max = uh[curr][j][i];
	if (max)
		return 1. / max;
	else
		return 1;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int kolvo;
			double k;
			wchar_t buff[40];
			std::thread p;
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_SOLUTION:
				kolvo = GetWindowTextW(EDITC1, buff, 40);
				buff[kolvo] = '\0';
				C1 = _wtof(buff);
				kolvo = GetWindowTextW(EDITC2, buff, 40);
				buff[kolvo] = '\0';
				C2 = _wtof(buff);
				kolvo = GetWindowTextW(EDITA, buff, 40);
				buff[kolvo] = '\0';
				a = _wtof(buff);
				kolvo = GetWindowTextW(EDITB, buff, 40);
				buff[kolvo] = '\0';
				b = _wtof(buff);
				kolvo = GetWindowTextW(EDITT, buff, 40);
				buff[kolvo] = '\0';
				T = _wtof(buff);
				kolvo = GetWindowTextW(EDITALPHA, buff, 40);
				buff[kolvo] = '\0';
				alpha = _wtof(buff);
				p =std::thread::thread(FindAnswer);
				p.detach();
                break;
			case IDM_INSTRUCTION:
				MessageBox(hWnd, L"График показывается для текущего слоя T", L"Инструкция", MB_OK);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_GRAPHIC:
				kolvo = GetWindowTextW(EDITTAU, buff, 40);
				currT= _wtoi(buff);
				if (!ready[currT]) { MessageBox(hWnd, L"Слой не готов", L"Ошибка", MB_OK); break; }
				GLFWwindow* window;
				if (!glfwInit())
				{
					MessageBox(hWnd, L"Ошибка инициализации OpenGL",L"Ошибка",MB_OK);
					break;
				}
				window = glfwCreateWindow(1240, 1240, "Hello World", NULL, NULL);
				if (!window)
				{
					glfwTerminate();
					MessageBox(hWnd, L"Ошибка OpenGL", L"Ошибка", MB_OK);
					break;
				}
				glfwMakeContextCurrent(window);
				glfwSetMouseButtonCallback(window, mouse_button_callback);
				glfwSetCursorPosCallback(window, mouse_button_rotate);
				//glFrustum(-2., 2., -2., 2., -21., 21.);
				//glTranslated(-.5, .5, -1.);
				glRotatef(-30, 1, 0, 0);
				glfwSetKeyCallback(window, key_callback);
				k = FindMax(uh,currT);
				while (!glfwWindowShouldClose(window))
				{
					/* Render here */
					double ratio;
					ratio = 1.;
					glClear(GL_COLOR_BUFFER_BIT);
					int i=0, j=0;
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					glOrtho(-ratio, ratio, -2.f, 2.f, 2.f, -2.f);
					glMatrixMode(GL_MODELVIEW);
					glBegin(GL_LINE_STRIP);
						glVertex3d(-1/2,-1/2,0.);
						glVertex3d(1/2,-1/2,0.);
						glVertex3d(1/2, 1/2, 0.);
						glVertex3d(-1/2, 1/2, 0.);
						glVertex3d(-1/2, -1/2, 0.);
						//glVertex3d(-1/2, -1/2, 1.0);
					glEnd();
					for (double x = -1/2; i < 11; x += .1,i++)
					{
						glBegin(GL_LINE_STRIP);
						for (double y = -1/2; j < 11; y += .1,j++)
							glVertex3d(x, y, uh[currT][j][i]*k);
						glEnd();
						j = 0;
					}
					i = 0; j = 0;
					for (double y = -1/2; j < 11; y += .1, j++)
					{
						glBegin(GL_LINE_STRIP);
						for (double x = -1/2; i < 11; x += .1, i++)
							glVertex3d(x, y, uh[currT][j][i]*k);
						i = 0;
						glEnd();
					}
					/* Swap front and back buffers */
					glfwSwapBuffers(window);
					/* Poll for and process events */
					glfwPollEvents();
				}
				glfwTerminate();
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		AddControls(hWnd);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
		int wmId = LOWORD(wParam);
		int kolvo;
		switch (wmId) {
		case IDOK:
			wchar_t buff[40];
			kolvo = GetDlgItemTextW(hDlg, ID_C1, buff, 40);
			buff[kolvo] = '\0';
			C1 = _wtof(buff);
			kolvo = GetDlgItemTextW(hDlg, ID_C2, buff, 40);
			buff[kolvo] = '\0';
			C2 = _wtof(buff);
			kolvo = GetDlgItemTextW(hDlg, ID_A, buff, 40);
			buff[kolvo] = '\0';
			a = _wtof(buff);
			kolvo = GetDlgItemTextW(hDlg, ID_B, buff, 40);
			buff[kolvo] = '\0';
			b = _wtof(buff);
			kolvo = GetDlgItemTextW(hDlg, ID_T, buff, 40);
			buff[kolvo] = '\0';
			T = _wtof(buff);
			kolvo = GetDlgItemTextW(hDlg, ID_ALPHA, buff, 40);
			buff[kolvo] = '\0';
			alpha = _wtof(buff);
			FindAnswer();
			EndDialog(hDlg, NULL);
			break;
		case IDCANCEL:
			EndDialog(hDlg, NULL);
			break;
		}
        break;
    }
    return (INT_PTR)FALSE;
}
double F(double x, double y, double t)
{
	return C1 * t * pow(E, -alpha * ((x - 7 * a / 8) * (x - 7 * a / 8) + (y - 3 * b / 8) * (y - 3 * b / 8)));
}
double v(double x, double y) {
	return  0;
}
double g1(double x, double t) {
	return 0;
}
double g2(double y, double t) {
	return C2 * t * sin(PI * y / b);
}
double g3(double x, double t) {
	return 0;
}
double g4(double y, double t) {
	return C2 * t * sin(PI * y / b);
}

void FindAnswer() {
	hx = a / 10;
	hy = b / 10;
	ht = T / 10;
	for (int i = 0; i <= 10; i++)
		for (int j = 0; j <= 10; j++)
			uh[0][j][i] = v(i * hx, j * hy);
	for (int i = 0; i <= 10; i++)
	{
		uh[0][0][i] = g1(i * hx, 0);
		uh[0][i][0] = g2(i * hy, 0);
		uh[0][10][i] = g3(i * hx, 0);
		uh[0][i][10] = g4(i * hy, 0);
	}
	ready[0] = 1;
	for (int k = 0; k < 10; k++)
	{
		GetNextTimeLayer(k);
		ready[k + 1] = 1;
	}
}
void GetNextTimeLayer(int curr) {
	double subuh[11][11];
	double otvet[11][11];
	double a[11];
	double b[11];
	double c[11];
	double f[11];
	double taux = ht / hx * hx;
	double tauy = ht / hy * hy;
	for (int j = 0; j < 11; j++) {
		for (int i = 0; i < 11; i++) {
			a[i] = taux;
			b[i] = -2*taux - 1;
			c[i] = taux;
			f[i] = -uh[curr][j][i] ;
		}
		f[0] = g2(j * hy, curr * ht);
		f[10] = g4(j * hy, curr * ht);
		c[0] = 0;
		a[10] = 0;
		Progonka(11, a, b, c, f, subuh[j]);
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			a[j] = tauy;
			b[j] = -2*tauy - 1;
			c[j] = tauy;
			f[j] = -subuh[j][i] - F(i*hx,j*hy,curr*ht);
		}
		f[0] = g1(i * hx, (curr) * ht);
		f[10] = g3(i * hx, (curr) * ht);
		c[0] = 0;
		a[10] = 0;
		Progonka(11, a, b, c, f, otvet[i]);
	}
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			uh[curr + 1][j][i] = otvet[j][i];
}
/**
 * n - число уравнений (строк матрицы)
 * b - диагональ, лежащая над главной (нумеруется: [0;n-2])
 * c - главная диагональ матрицы A (нумеруется: [0;n-1])
 * a - диагональ, лежащая под главной (нумеруется: [1;n-1])
 * f - правая часть (столбец)
 * x - решение, массив x будет содержать ответ
 */
void Progonka(int n, double* a, double* c, double* b, double* f, double* x)
{
	double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i] / c[i - 1];
		c[i] = c[i] - m * b[i - 1];
		f[i] = f[i] - m * f[i - 1];
	}

	x[n - 1] = f[n - 1] / c[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = (f[i] - b[i] * x[i + 1]) / c[i];
	}
}