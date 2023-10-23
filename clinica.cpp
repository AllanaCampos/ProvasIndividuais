#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class Data{
    private:

        int dia;
        int mes;
        int ano;

    public:
        void setDia(int _dia){
            this->dia = _dia;
        }
        int getDia(){
            return this->dia;
        }
        void setMes(int _mes){
            this->mes = _mes;
        }
        int getMes(){
            return this->mes;
        }
        void setAno(int _ano){
            this->ano = _ano;
        }
        int getAno(){
            return this->ano;
        }
        void imprimirData(){
            cout << this->dia << "/" << this->mes << "/" << this->ano << endl;
        }
        static bool dataValida(Data *data){
            if ((data->mes < 1) || (data->mes > 12)) 
                return false; 
            int diaMax = 31; 
            if(data->mes == 2){ 
                diaMax = 28; 
                if(data->ano%4==0) 
                    diaMax = 29; 
            }
            if((data->mes==4) || (data->mes == 6)|| (data->mes == 9) || (data->mes ==11)) 
                diaMax = 30; 
            if((data->dia >= 1) && (data->dia <= diaMax)) 
                return true; 
            else return false; 
            
        }

        static Data * leData(){
            Data * novaData = new Data(); 
            int _dia, _mes, _ano; 
            do {
                cout << "Digite o dia, o mes e o ano: " << endl;
                cin >> _dia >> _mes >> _ano; 
                novaData->setDia(_dia); 
                novaData->setMes(_mes);
                novaData->setAno(_ano);
            } while(!Data::dataValida(novaData)); 
            return novaData; 
        }
};

class Paciente{
    private:

        string CPF;
        string nome;
        Data *dtNascimento;

    public:

        void setCPF(string _CPF){
            this->CPF = _CPF;
        }
        string getCPF(){
            return this->CPF;
        }
        void setNome(string _nome){
            this->nome = _nome;
        }
        string getNome(){
            return this->nome;
        }
        void setDtNascimento(Data *_dtNascimento){
            this->dtNascimento = _dtNascimento;
        }
        Data * getDtNascimento(){
            return this->dtNascimento;
        }
        static void leCPF(Paciente* &p){
            string cpf;
            do{
                cout <<"Digite o CPF do paciente com o seguinte formato: xxx.xxx.xxx-xx" << endl;
                getline(cin, cpf);
                p->setCPF(cpf);
            }while(!Paciente::validarCPF(cpf));
        }
        static void addPaciente(vector<Paciente*> &pacientes){
            Paciente *p = new Paciente();
            string nome, cpf;
            Data * nascimento;
            cout <<"Digite o nome do paciente:" << endl;
            cin.ignore();
            getline(cin, nome);
            p->setNome(nome);
            Paciente::leCPF(p);
            cout << "Informe a data de nascimento. ";
            nascimento = Data::leData();
            p->setDtNascimento(nascimento);
            pacientes.push_back(p);
        }
        static void deletePaciente(vector<Paciente *> &pacientes){
            string cpf;
            int pos;
            cout << "Digite o CPF do paciente que deve ser excluido" << endl;
            cin.ignore();
            getline(cin, cpf);
            pos = Paciente::getPosPaciente(cpf, pacientes);
            if(pos == -1){
                cout << "Paciente nao encontrado" << endl;
            }
            else{
                pacientes.erase(pacientes.begin() + pos);
                cout << "Paciente excluido" << endl;
            }
        }
        static void updatePaciente(vector<Paciente *> &pacientes){
            Paciente * atualizado;
            string cpf, nome;
            char op;
            int pos;
            cout << "Digite o CPF do paciente que deve atualizar o cadastro" << endl;
            cin.ignore();
            getline(cin, cpf);
            pos = Paciente::getPosPaciente(cpf, pacientes);
            if(pos == -1){
                cout << "Paciente nao encontrado" << endl;
            }
            else{
                atualizado = pacientes[pos];
                cout << "Nome: " << atualizado->getNome() << endl;
                cout << "Data de nascimento: ";
                atualizado->getDtNascimento()->imprimirData();
                do{
                    cout << "Deseja alterar o nome? (s/n)" << endl;
                    cin >> op;
                    if(op == 's'){
                        cout << "Digite o novo nome" << endl;
                        cin.ignore();
                        getline(cin, nome);
                        atualizado->setNome(nome);
                    }
                }while (op!='n' && op!='s');
                op = 'a';
                do{
                    cout << "Deseja alterar a data de nascimento? (s/n)" << endl;
                    cin >> op;
                    if(op == 's'){
                        Data * data;
                        cout << "Digite a nova data. ";
                        data = Data::leData();
                        atualizado->setDtNascimento(data);
                    }
                }while (op!='n' && op!='s');
            }
        }
        static int getPosPaciente(string cpf, vector<Paciente *> pacientes){
            int pos = 0;
            for(Paciente * p : pacientes){
                if(p->getCPF() == cpf){
                    return pos;
                }
                pos++;
            }
            return -1;
        }
        static void findPaciente(vector<Paciente *> pacientes){
            Paciente *encontrado;
            string cpf;
            int pos;
            cout << "Digite o CPF do paciente que deseja localizar" << endl;
            cin.ignore();
            getline(cin, cpf);
            pos = Paciente::getPosPaciente(cpf, pacientes);
            if(pos == -1){
                cout << "Paciente não encontrado" << endl;
            }
            else{
                encontrado = pacientes[pos];
                cout << "Nome: " << encontrado->getNome() << endl;
                cout << "Data de nascimento: ";
                encontrado->getDtNascimento()->imprimirData();
            }
        }
        static void listarPacientes(vector<Paciente *> pacientes){
            cout << "<----------Pacientes cadastrados---------->" << endl;
            for(auto p : pacientes){
                cout << "Nome: " << p->getNome() << endl;
                cout << "CPF: " << p->getCPF() << endl;
                cout << "Data de Nascimento: ";
                p->getDtNascimento()->imprimirData();
            }
        }
        static bool validarCPF(string cpf){
            if(cpf.length() < 14){
                cout << "CPF invalido." << endl;
                return false;
            }
            for(int i = 0; i < int(cpf.length()); i++){
                if(i == 3 || i == 7){
                    if(cpf[i]!= '.'){
                        cout << "CPF invalido." << endl;
                        return false;
                    }
                }
                else if(i == 11){
                    if(cpf[i] != '-'){
                        cout << "CPF invalido." << endl;
                        return false;
                    }
                }
                else{
                    if(!(cpf[i] >= '0' && cpf[i]<='9')){
                        cout << "CPF invalido." << endl;
                        return false;
                    }
                }

            }
            return true;
        }


};

class Medico{
    private:

        string CRM;
        string nome;
        string especialidade;

    public:

        string getCRM(){
            return this->CRM;
        }
        void setCRM(string _CRM){
            this->CRM = _CRM;
        }
        string getNome(){
            return this->nome;
        }
        void setNome(string _nome){
            this->nome = _nome;
        }
        string getEspecialidade(){
            return this->especialidade;
        }
        void setEspecialidade(string _especialidade){
            this->especialidade = _especialidade;
        }
        static void addMedico(vector<Medico *> &medicos){
            Medico *m = new Medico();
            string nome, especialidade, crm;
            cout << "Digite o nome do medico:" << endl;
            cin.ignore();
            getline(cin, nome);
            m->setNome(nome);
            cout << "Digite o CRM do medico:" << endl;
            getline(cin, crm);
            m->setCRM(crm);
            cout << "Digite a especialidade do medico:" << endl;
            getline(cin, especialidade);
            m->setEspecialidade(especialidade);
            medicos.push_back(m);
        }
        static void deleteMedico(vector<Medico *> &medicos){
            string crm;
            int pos;
            cout << "Digite o CRM do medico que deve ser excluido" << endl;
            cin.ignore();
            getline(cin, crm);
            pos = Medico::getPosMedico(crm, medicos);
            if(pos == -1){
                cout << "Medico nao encontrado" << endl;
            }
            else{
                medicos.erase(medicos.begin() + pos);
                cout << "Paciente excluido" << endl;
            }
        }
        static int getPosMedico(string crm, vector<Medico *> medicos){
            int pos = 0;
            for(auto * m : medicos){
                if(m->getCRM() == crm){
                    return pos;
                }
                pos++;
            }
            return -1;
        }
        static void updateMedico(vector<Medico *> &medicos){
            Medico * atualizado;
            string crm, nome, especialidade;
            char op;
            int pos;
            cout << "Digite o CRM do medico que deve atualizar o cadastro" << endl;
            cin.ignore();
            getline(cin, crm);
            pos = Medico::getPosMedico(crm, medicos);
            if(pos == -1){
                cout << "Medico nao encontrado" << endl;
            }
            else{
                atualizado = medicos[pos];
                cout << "Nome: " << atualizado->getNome() << endl;
                cout << "Especialidade: " << atualizado->getEspecialidade() << endl;
                do{
                    cout << "Deseja alterar o nome? (s/n)" << endl;
                    cin >> op;
                    if(op == 's'){
                        cout << "Digite o novo nome" << endl;
                        cin.ignore();
                        getline(cin, nome);
                        atualizado->setNome(nome);
                    }
                }while (op!='n' && op!='s');
                op = 'a';
                do{
                    cout << "Deseja alterar a especialidade? (s/n)" << endl;
                    cin >> op;
                    if(op == 's'){
                        cout << "Digite a nova especialidade" << endl;
                        cin.ignore();
                        getline(cin, especialidade);
                        atualizado->setEspecialidade(especialidade);
                    }
                }while (op!='n' && op!='s');
            }
        }
        static void listarMedicos(vector<Medico *> medicos){
            cout << "<----------Medicos cadastrados---------->" << endl;
            for(auto m : medicos){
                cout << "Nome: " << m->getNome() << endl;
                cout << "CRM: " << m->getCRM() << endl;
                cout << "Especialidade: " << m->getEspecialidade() << endl;
            }
        }
        static void findMedico(vector<Medico *> medicos){
            Medico *encontrado;
            string crm;
            int pos;
            cout << "Digite o CRM do medico que deseja localizar" << endl;
            cin.ignore();
            getline(cin, crm);
            pos = Medico::getPosMedico(crm, medicos);
            if(pos == -1){
                cout << "Medico não encontrado" << endl;
            }
            else{
                encontrado = medicos[pos];
                cout << "Nome: " << encontrado->getNome() << endl;
                cout << "Especialidade: " << encontrado->getEspecialidade() << endl;
            }
        }
};

void menuPacientes(vector<Paciente *> &pacientes);
void menuMedicos(vector<Medico *> &medicos);

int main(){
    vector<Paciente *> pacientes;
    vector<Medico *> medicos;
    int opcao;
    do{
        cout << "<----------Menu---------->" << endl;
        cout << "1- Gerenciar pacientes" << endl;
        cout << "2- Gerenciar medicos" << endl;
        cout << "0- Sair" << endl;
        cin >> opcao;
        switch (opcao){
        case 1:
            menuPacientes(pacientes);
            break;
        case 2:
            menuMedicos(medicos);
            break;
        }
    }while (opcao != 0);
    return 0;
}

void menuPacientes(vector<Paciente*> &pacientes){
    int opcao;
    do{
        cout << "<----------Gestao de Pacientes---------->" << endl;
        cout << "1- Incluir" << endl;
        cout << "2- Excluir" << endl;
        cout << "3- Alterar" << endl;
        cout << "4- Listar" << endl;
        cout << "5- Localizar" << endl;
        cout << "0- Sair" << endl;

        cin >> opcao;

        switch (opcao){
        case 1:
            Paciente::addPaciente(pacientes);
            break;
        case 2:
            Paciente::deletePaciente(pacientes);
            break;
        case 3:
            Paciente::updatePaciente(pacientes);
            break;
        case 4:
            Paciente::listarPacientes(pacientes);
            break;
        case 5:
            Paciente::findPaciente(pacientes);
            break;
        }

    }while(opcao != 0);
}
void menuMedicos(vector<Medico*> &medicos){
    int opcao;
    do{
        cout << "<----------Gestao de Medicos---------->" << endl;
        cout << "1- Incluir" << endl;
        cout << "2- Excluir" << endl;
        cout << "3- Alterar" << endl;
        cout << "4- Listar" << endl;
        cout << "5- Localizar" << endl;
        cout << "0- Sair" << endl;

        cin >> opcao;

        switch (opcao){
        case 1:
            Medico::addMedico(medicos);
            break;
        case 2:
            Medico::deleteMedico(medicos);
            break;
        case 3:
            Medico::updateMedico(medicos);
            break;
        case 4:
            Medico::listarMedicos(medicos);
            break;
        case 5:
            Medico::findMedico(medicos);
            break;
        }

    }while(opcao != 0);
}
