#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

struct Instruction
{
    const string opcode;
    int cycles;
    int cont;
};

struct Organization
{
    int cycles_cont;
    float cpi;
    float run_rate;
};

int main()
{
    setlocale(LC_ALL, "Portuguese");
    ifstream inputFile("doc.txt");

    if (!inputFile)
    {
        cerr << "\nNão existe nenhum arquivo com o nome de "
                "doc.txt"
                " no diretório do projeto.";
        return 0;
    }

    int option = 0;
    float clock = 0;
    string line;
    int instruction_cont = 0;

    Instruction U = {"0110111", 5, 0};
    Instruction J = {"1101111", 5, 0};
    Instruction B = {"1100011", 5, 0};
    Instruction L = {"0000011", 5, 0};
    Instruction S = {"0100011", 5, 0};
    Instruction I = {"0010011", 5, 0};
    Instruction R = {"0110011", 5, 0};

    Organization X = {0, 0, 0};
    Organization Y = {0, 0, 0};

    cout << "\nCOMPARADOR DE ORGANIZAÇÃO";
    cout << "\nCertifique-se de substituir o conteúdo do arquivo doc.txt no diretório pelo seu dump file!";

    for (int t = 0; t < 2; t++)
    {
        cout << "\nORGANIZAÇÃO[" << t + 1 << "]:";

        cout << "\nVocê deseja adicionar a quantidade de ciclos por Instrução ou seguir com a tabela abaixo?";
        cout << "\nU: " << U.opcode << "\nJ: " << J.opcode << "\nB: " << B.opcode << "\nL: " << L.opcode << "\nS: " << S.opcode << "\nI: " << I.opcode << "\nR: " << R.opcode << endl
             << endl;
        cout << "\nDigite 1 para adicionar e 0 para seguir com a tabela!\n";
        cin >> option;

        if (option == 1)
        {
            cout << "\nU: ";
            cin >> U.cycles;
            cout << "\nJ: ";
            cin >> J.cycles;
            cout << "\nB: ";
            cin >> B.cycles;
            cout << "\nL: ";
            cin >> L.cycles;
            cout << "\nS: ";
            cin >> S.cycles;
            cout << "\nI: ";
            cin >> I.cycles;
            cout << "\nR: ";
            cin >> R.cycles;
        }

        cout << "\n\nQual o tempo de clock? Em nanosegundos\n";
        cin >> clock;

        while (getline(inputFile, line))
        {
            instruction_cont++;
            int length = line.length();
            for (int i = 0; i < length; i += 32)
            {
                if (i + 32 <= length)
                {
                    string segment = line.substr(i, 32);
                    string last_seven = segment.substr(25, 7);

                    if (last_seven == U.opcode)
                    {
                        U.cont++;
                    }

                    if (last_seven == J.opcode)
                    {
                        J.cont++;
                    }

                    if (last_seven == B.opcode)
                    {
                        B.cont++;
                    }

                    if (last_seven == L.opcode)
                    {
                        L.cont++;
                    }

                    if (last_seven == S.opcode)
                    {
                        S.cont++;
                    }

                    if (last_seven == I.opcode)
                    {
                        R.cont++;
                    }

                    if (last_seven == R.opcode)
                    {
                        R.cont++;
                    }
                }
            }
        }

        int cycles_cont = ((U.cont * U.cycles) + (J.cont * J.cycles) + (B.cont * B.cycles) + (L.cont * L.cycles) + (S.cont * S.cycles) + (I.cont * I.cycles) + (R.cont * R.cycles));
        float cpi = cycles_cont / instruction_cont;
        float run_rate = (instruction_cont * cpi * clock);

        if (t == 1)
        {
            X.cycles_cont = cycles_cont;
            X.cpi = cpi;
            X.run_rate = run_rate;
        }
        else
        {
            Y.cycles_cont = cycles_cont;
            Y.cpi = cpi;
            Y.run_rate = run_rate;
        }

        cout << "\nO dump file apresenta " << instruction_cont << " instruções.";
        cout << "\nAo todo foram " << cycles_cont << " ciclos";
        cout << "\nCPI: " << cpi;
        cout << "\nA taxa de execução é de: " << run_rate;
    }

    inputFile.close();

    if (X.run_rate < Y.run_rate)
    {
        float diference = Y.run_rate / X.run_rate;
        cout << "\nA arquitetura 1 é " << diference << " mais rápida.";
    }
    else
    {
        float diference = X.run_rate / Y.run_rate;
        cout << "\nA arquitetura 2 é " << diference << " mais rápida.";
    }

    return 0;
}
