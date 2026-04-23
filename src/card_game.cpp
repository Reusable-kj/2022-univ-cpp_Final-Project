#include <stdlib.h> //rand, srand 사용을 위한 헤더
#include <time.h> //time(null)을 사용하기 위한 헤더
#include <iostream>
#include <windows.h> //cmd 화면 조작을 위한 헤더

using namespace std;
#define SIZE 4
//게임을 단순화 시키기 위해 조커를 제외해 짝수개수로 맞춰주었습니다

void gamin();
void setbar() //게임화면 설정을 ==== 바(bar)로 해주기
{
    for (int i = 0; i < 53; i++)
        cout << "=";
    cout << endl;
}

struct CD //배열 값을 복사시키기 위한 구조체 선언
{
    int deck[SIZE][SIZE] = { 0 };
};

struct CD setdeck() //덱을 섞어주는 함수 선언
{

    int i, j;
    int x, y;
    srand(time(NULL));

    struct CD t;
    int dev = SIZE * SIZE / 2;

    for (i = 1; i < dev + 1; i++) // 1~8의 숫자를
    {
        for (j = 0; j < 2; j++) // 배열에 각각 2개씩 집어넣는다.
        {
            do
            {
                x = rand() % SIZE;
                y = rand() % SIZE;
            } while (t.deck[x][y] != 0); // 인덱스 위치가 겹치지 않도록 해주는 함수
            t.deck[x][y] = i;
        }
    }
    return t;
}



int main(void)
{

    system("mode con cols=53 lines=40");

    int stn;
    srand(time(NULL));

    int an_deck[SIZE][SIZE] = { 0 }; // 초기 화면 표시값 0 0 0으로 고정

startin:                            // 프로그램의 시작점
    system("cls");
    setbar();

    cout << endl << " 이 게임은 카드뒤집기 (같은 숫자 고르기) 게임입니다." << endl << " 시작하려면 1을, 도움말을 보려면 0을 입력해주세요." << endl;
    cin >> stn;

    switch (stn) {
    case 0: //도움말
        cout << endl << " 4*4배열 카드가 있습니다." << endl << " 사용자는 [세로][가로] 좌표를 입력하여 카드를 두번 뒤집게 됩니다." << endl << " 뒤집힌 카드는 일시적으로 화면에 표기되며, 같은 카드를 뽑은 경우 영구적으로 표기됩니다." << endl << " 목숨은 총 8개이며, 틀릴때마다 하나씩 차감됩니다." << endl;
        cout << endl << " 재시작하려면 1을 눌러주십시오." << endl;
        cin >> stn;
        if (stn == 1)
            break;

    case 1: //프로그램 시작
        system("cls");
        setbar();
        gamin();
        cout << "게임이 끝났습니다. 재시작해주십시오.";
        break;
    }

    goto startin; // 재시작하기 위한 위치 지정문_시작점으로 돌아가라는 명령


}

void gamin()
{
    int heart = 8, st = 1;
    int ln, t1_ck, t2_ck, a, b, c, d;
    int an_deck[SIZE][SIZE] = { 0 };
    int line[2] = {0};

    struct CD t = setdeck(); //구조체 t.deck의 숫자들을 불러오는 코드

    while (st) //while문 조건이 참(1)일 경우에 반복되는것을 이용한 설계, 게임 종료시 st = 0 반환.
    {
        system("cls");
        setbar();
        cout << endl;
        for (int i = 0; i < SIZE; i++) //프로그램 시작, 사용자에게 초기 배열 위치 표시.
        {
            for (int j = 0; j < SIZE; j++)
            {
                cout << " " << an_deck[i][j];
            }
            cout << endl << endl;
        }

        cout << "   남은 목숨: " << heart << endl << endl;
        cout << " 카드를 선택해주십시오" << endl << " [세로][가로]" << endl;
        cout << " 첫번째 선택:";

        for (int i = 0; i < 2; i++)
        {
        re1:
            cin >> ln;
            if (ln > 4)
            {
                cout << endl << "숫자가 너무 큽니다! 1~4 내로 입력해주십시오\n:";
                goto re1;
            }
            if(ln == 0)
            {
                cout << endl << " 0은 입력값이 아닙니다. 1~4 내로 입력해주십시오\n:";
                goto re1;
            }
            line[i] = ln-1;
        }
        a = line[0];
        b = line[1];                      //틀렸을때 해당 인덱스를 0으로 돌리기 위한 값
        t1_ck = t.deck[a][b]; // 행, 열값을 받아 무작위 덱에서 인덱스값 가져오기
        an_deck[a][b] = t1_ck;

        cout << " 두번째 선택:";
        for (int i = 0; i < 2; i++)
        {
        re2:
            cin >> ln;
            if (ln > 4)
            {
                cout << endl << "숫자가 너무 큽니다! 1~4 내로 입력해주십시오\n:";
                goto re2;
            } 
            if (ln == 0)
            {
                cout << endl << " 0은 입력값이 아닙니다. 1~4 내로 입력해주십시오\n:";
                goto re2;
            }
            line[i] = ln-1;
        }
        c = line[0];
        d = line[1];
        t2_ck = t.deck[c][d]; // 위 라인과 같은 의미
        an_deck[c][d] = t2_ck;

        cout << t1_ck << " " << t2_ck << endl; // 작동 되는지 확인용

        if (t1_ck == t2_ck)
        {
            cout << "\n 축하합니다 맞추셨습니다!" << endl;
            setbar();
            Sleep(2500);
        }
        else {
            system("cls");
            heart = heart - 1;
            setbar();
            cout << "\n\n 틀리셨습니다. 남은 목숨은 " << heart << "개 입니다.\n" << endl;

            for (int i = 0; i < SIZE; i++) //선택한 배열 값 표기
            {
                for (int j = 0; j < SIZE; j++)
                {
                    cout << " " << an_deck[i][j];
                }
                cout << endl << endl;
            }
            setbar();

            Sleep(2500); //2.5초간 화면 표기

            an_deck[a][b] = 0;
            an_deck[c][d] = 0;
        }
        ln = 0;

        for (int i = 0; i < SIZE; i++) //an_deck 함수가 모두 0이 아닌 숫자로 표기될때, 모두 맞추었다는것을 의미함. => 게임 종료
        {
            for (int j = 0; j < SIZE; j++)
                if (an_deck[i][j] != 0)
                {
                    ln = ln + 1;
                    if (ln == 16)
                    {
                        cout << "\n 축하합니다! 남은 목숨 " << heart << "개로 모두 맞추셨습니다!" << endl;
                        setbar();
                        Sleep(3000);
                        st = 0;
                    }
                }

        }
        if (heart == 0)
        {
            cout << "\n 목숨이 모두 소진되었습니다. 게임을 재시작해주십시오." << endl;
            setbar();
            Sleep(3000);
            st = 0;
        }
    }
}