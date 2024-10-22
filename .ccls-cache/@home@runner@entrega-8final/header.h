//Parametros struct
struct Tpessoa{
char nome[30];
char sobrenome[40];
char sexo;
int idade;
};

int LerSalaTri();
int LerDoses();
int EscolhaMenu();
int EscolhaSubMenu();
void flush_in();
void lerString(char s[], int tam);
void imprimeFilaPessoas(struct Tpessoa fila[], int tamanho);
int fimDia();
struct Tpessoa lerPessoa();