#include <windows.h>
#include <CommCtrl.h>

typedef struct ScrumMaster
{
    char name[256];
    char surname[256];
    int count;
    double score;
    char date[11];
} master_t;

enum
{
    STATIC_ID = 0,
    STATIC_ID_NAME,
    STATIC_ID_SURNAME,
    STATIC_ID_COUNT,
    STATIC_ID_SCORE,
    STATIC_ID_DATE,

    ID_CB,
    ID_TIMER
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE hInst);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    const char g_szClassName[] = "myWindowClass";

    HINSTANCE hInst = hInstance;
    WNDCLASSEX wc;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    g_szClassName,
                    "ScrumMasters",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                    NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE hInst)
{
    static HWND hGroupBox, hStaticTicks, hStaticIndex;
    static HWND hStaticNameT, hStaticSurnameT, hStaticCountT, hStaticScoreT, hStaticDateT;
    static HWND hStaticName, hStaticSurname, hStaticCount, hStaticScore, hStaticDate;

    static int ticks = 0;
    master_t masters[3] =
    {
        {"Ivan", "Burlaka", 3, 3.4, "1950-12-12"},
        {"Jon", "Adams", 5, 4.8, "1887-02-05"},
        {"Taras", "Shevchenko", 4, 3.0, "1999-08-11"}
    };

    switch(msg)
    {
    case WM_CREATE:
    {
        hGroupBox = CreateWindow(WC_BUTTON, "ScrumMaster",
                                 WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_GROUP,
                                 40, 10, 300, 180,
                                 hwnd, NULL, hInst, NULL);


        hStaticNameT = CreateWindowEx(0, WC_STATIC, "Name:",
                                      WS_CHILD | WS_VISIBLE,
                                      10, 30, 43, 15,
                                      hGroupBox, NULL, hInst, NULL);

        hStaticSurnameT = CreateWindowEx(0, WC_STATIC, "Surname:",
                                         WS_CHILD | WS_VISIBLE,
                                         10, 60, 65, 15,
                                         hGroupBox, NULL, hInst, NULL);

        hStaticCountT = CreateWindowEx(0, WC_STATIC, "Count:",
                                       WS_CHILD | WS_VISIBLE,
                                       10, 90, 43, 15,
                                       hGroupBox, NULL, hInst, NULL);

        hStaticScoreT = CreateWindowEx(0, WC_STATIC, "Score:",
                                       WS_CHILD | WS_VISIBLE,
                                       10, 120, 43, 15,
                                       hGroupBox, NULL, hInst, NULL);

        hStaticDateT = CreateWindowEx(0, WC_STATIC, "Date:",
                                      WS_CHILD | WS_VISIBLE,
                                      10, 150, 35, 15,
                                      hGroupBox, NULL, hInst, NULL);



        hStaticName = CreateWindowEx(0, WC_STATIC, "",
                                     WS_CHILD | WS_VISIBLE,
                                     150, 30, 120, 15,
                                     hGroupBox, (HMENU)STATIC_ID_NAME, hInst, NULL);

        hStaticSurname = CreateWindowEx(0, WC_STATIC, "",
                                        WS_CHILD | WS_VISIBLE,
                                        150, 60, 120, 15,
                                        hGroupBox, (HMENU)STATIC_ID_SURNAME, hInst, NULL);

        hStaticCount = CreateWindowEx(0, WC_STATIC, "",
                                      WS_CHILD | WS_VISIBLE,
                                      150, 90, 120, 15,
                                      hGroupBox, (HMENU)STATIC_ID_COUNT, hInst, NULL);

        hStaticScore = CreateWindowEx(0, WC_STATIC, "",
                                      WS_CHILD | WS_VISIBLE,
                                      150, 120, 120, 15,
                                      hGroupBox, (HMENU)STATIC_ID_SCORE, hInst, NULL);

        hStaticDate = CreateWindowEx(0, WC_STATIC, "",
                                     WS_CHILD | WS_VISIBLE,
                                     150, 150, 120, 15,
                                     hGroupBox, (HMENU)STATIC_ID_DATE, hInst, NULL);



        CreateWindowW(L"button", L"Update timer",
                      WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_AUTOCHECKBOX,
                      210, 210, 105, 15,
                      hwnd, (HMENU)ID_CB, NULL, NULL);
        CheckDlgButton(hwnd, ID_CB, BST_CHECKED);

        hStaticTicks = CreateWindowEx(0, WC_STATIC, "Default",
                                 WS_CHILD | WS_VISIBLE,
                                 50, 200, 70, 15,
                                 hwnd, (HMENU)STATIC_ID, hInst, NULL);

        hStaticIndex = CreateWindowEx(0, WC_STATIC, "Default",
                                 WS_CHILD | WS_VISIBLE,
                                 50, 220, 70, 15,
                                 hwnd, (HMENU)STATIC_ID, hInst, NULL);

        const int TIMER_TICK = 1000;
        int ret = SetTimer(hwnd, ID_TIMER, TIMER_TICK, NULL);
        if(ret == 0)
            MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
        break;
    }
    case WM_TIMER:
    {
        int checked = IsDlgButtonChecked(hwnd, ID_CB);
        if (checked)
        {
            char count[10] = "";
            char score[10] = "";
            SetWindowText(hStaticName, masters[ticks%3].name);
            SetWindowText(hStaticSurname, masters[ticks%3].surname);
            sprintf(count, "%i", masters[ticks%3].count);
            SetWindowText(hStaticCount, TEXT(count));
            sprintf(score, "%.1f", masters[ticks%3].score);
            SetWindowText(hStaticScore, TEXT(score));
            SetWindowText(hStaticDate, masters[ticks%3].date);

            char index[10] = "";
            sprintf(index, "Index: %i", ticks%3);
            SetWindowText(hStaticIndex, TEXT(index));

            ticks++;
            char buf[15] = "";
            sprintf(buf, "Ticks: %i", ticks);
            SetWindowText(hStaticTicks, TEXT(buf));
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
