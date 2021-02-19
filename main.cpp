#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <cstdio>

using namespace std;
struct Incidentes{
int poliza;
char patente[10];
int codigoIncidente;
char fecha[25];
char DNI_asegurado[20];
char DNI_otroConductor[20];
char direccion[50];
};

struct PolizadeAsegurados{
int poliza;
char DNI[20];
char nombre[10];
char apellido [10];
bool cuotaAlDia= true;
char patenteAuto [10];
bool activa = true;/*acalarar en el infoerme*/
int cdadIncidentes = 0;
};

void cargarPoliza(){
  FILE* polizas;
  PolizadeAsegurados pa;
  polizas = fopen("asegurados.BAK","ab");
  if(polizas){
     cout<<"*** Complete los siguientes datos para que la poliza pueda ser cargada para el cliente: " <<endl;
     cout<< "Numero de poliza: "<<endl;
     cin>> pa.poliza;
     cout<< "Patente del auto"<< endl;
     fflush(stdin);
     gets(pa.patenteAuto);
     cout<< "Nombre del cliente: "<< endl;
     fflush(stdin);
     gets(pa.nombre);
     cout << "Apellido del cliente"<<endl;
     fflush(stdin);
     gets (pa.apellido);
     cout<<"DNI del cliente"<< endl;
     cin>> pa.DNI;
     fwrite(&pa, sizeof(PolizadeAsegurados),1,polizas);
     fclose(polizas);
  }
return;
}

/*=====Si desea cargar incidentes al archivo para realizar las pruebas correspondientes, le dejamos programado esa parte!=====*/
/*void cargarIncidente(){
  FILE* inci;
  Incidentes in;
  inci = fopen("incidentes.BAK","ab");
  if(inci){
     cout<<"*** Complete los siguientes datos para que el incidente pueda ser cargado correctamente: " <<endl;
     cout<< "Codigo de Incidente: "<<endl;
     cin>> in.codigoIncidente;
     cout<< "N°Poliza"<< endl;
     cin>>in.poliza;
     cout<< "Fecha del Incidente: "<< endl;
     cin>>in.fecha;
     cout<<"Direccion del incidente"<< endl;
     fflush(stdin);
     gets(in.direccion);
     cout<<"Patente del Auto"<<endl;
     fflush(stdin);
     gets(in.patente);
     cout << "DNI del asegurado"<<endl;
     cin>>in.DNI_asegurado;
     cout<<"DNI de otro conductor"<< endl;
     cin>> in.DNI_otroConductor;
     fwrite(&in, sizeof(struct Incidentes),1,inci);
  }
  fclose(inci);
return;
}*/
/*void cargarProcesados(){
  FILE* inci;
  Incidentes in;
  inci = fopen("procesados.BAK","ab");
  if(inci){
     cout<<"*** Complete los siguientes datos para que el incidente pueda ser cargado correctamente: " <<endl;
     cout<< "Codigo de Incidente: "<<endl;
     cin>> in.codigoIncidente;
     cout<< "N°Poliza"<< endl;
     cin>>in.poliza;
     cout<< "Fecha del Incidente: "<< endl;
     cin>>in.fecha;
     cout<<"Direccion del incidente"<< endl;
     fflush(stdin);
     gets(in.direccion);
     cout<<"Patente del Auto"<<endl;
     fflush(stdin);
     gets(in.patente);
     cout << "DNI del asegurado"<<endl;
     cin>>in.DNI_asegurado;
     cout<<"DNI de otro conductor"<< endl;
     cin>> in.DNI_otroConductor;
     fwrite(&in, sizeof(struct Incidentes),1,inci);
  }
  fclose(inci);
return;
}*/
void desactivarPoliza(int numeroPoliza){
  FILE* polizas;
  PolizadeAsegurados pa;
  int existe = 0;
  polizas=fopen("asegurados.BAK", "rb+");
  fread(&pa,sizeof(PolizadeAsegurados),1,polizas);
  while (!feof(polizas)){
        if(numeroPoliza==pa.poliza){
           pa.activa = false;
           fseek(polizas,(-1)*sizeof(PolizadeAsegurados),SEEK_CUR);
           fwrite(&pa,sizeof(PolizadeAsegurados),1,polizas);
           cout<<"La poliza fue desactivada"<<endl;
           existe = 1;
           break;
        }
        fread(&pa,sizeof(PolizadeAsegurados),1,polizas);
  }
  if (existe==0)
      cout<<"No existe la poliza"<<endl;
  fclose(polizas);
return;
}

void busquedaPorDNI (char dniBuscado[]){
  FILE* poliza;
  PolizadeAsegurados pa;
  poliza = fopen("asegurados.BAK","rb");
  if (poliza){
      fread(&pa,sizeof(PolizadeAsegurados),1,poliza);
      while (!feof(poliza)){
             if(strcmp(dniBuscado, pa.DNI)==0){
                cout<< "****** EL USUARIO CON DNI "<< pa.DNI<<" POSEE LAS SIGUIENTE POLIZA******"<< endl;
                cout << "_______________________________________________________________________________________________" << endl;
                cout << "_______________________________________________________________________________________________" << endl;
                cout<< "****** LOS DATOS DE LA POLIZA "<< pa.poliza<< " SON ******"<< endl;
                cout<< "Estado de la poliza: " << pa.activa<< " **Si dice 1 la poliza esta activa, si dice 0 esta desactiva**"<< endl;
                cout<< "Estado de la cuota: " << pa.cuotaAlDia<< " **Si dice 1 la cuota esta al, si dice 0 no esta paga**"<< endl;
                cout<< "Nombre y apellido del cliente: "<< pa.nombre<< " "<< pa.apellido <<endl;
                cout<< "El DNI del cliente: "<< pa.DNI<< endl;
                cout<< "La patente del auto: "<< pa.patenteAuto<< endl;
                cout<< "Cantidad de incidentes: "<< pa.cdadIncidentes<<endl;
                cout << "_______________________________________________________________________________________________" << endl;
              }
             fread(&pa,sizeof(PolizadeAsegurados),1,poliza);
        }
  }
  fclose(poliza);
return;
}

void busquedaPorPoliza (int polizaBuscada){
  FILE* poliza;
  PolizadeAsegurados pa;
  poliza = fopen("asegurados.BAK","rb");
  if (poliza){
      fread(&pa,sizeof(PolizadeAsegurados),1,poliza);
      while (!feof(poliza)){
             if(polizaBuscada==pa.poliza){
                cout << "_______________________________________________________________________________________________" << endl;
                cout << "_______________________________________________________________________________________________" << endl;
                cout<< "****** LOS DATOS DE LA POLIZA "<< pa.poliza<< " SON ******"<< endl;
                cout<< "Estado de la poliza: " << pa.activa<< " **Si dice 1 la poliza esta activa, si dice 0 esta desactiva**"<< endl;
                cout<< "Estado de la cuota: " << pa.cuotaAlDia<< " **Si dice 1 la cuota esta al, si dice 0 no esta paga**"<< endl;
                cout<< "Nombre y apellido del cliente: "<< pa.nombre<< " "<< pa.apellido <<endl;
                cout<< "El DNI del cliente: "<< pa.DNI<< endl;
                cout<< "La patente del auto: "<< pa.patenteAuto<< endl;
                cout<< "Cantidad de incidentes: "<< pa.cdadIncidentes<<endl;
                cout << "_______________________________________________________________________________________________" << endl;
             }
      fread(&pa,sizeof(PolizadeAsegurados),1,poliza);
      }
  }
  fclose(poliza);
return;
}

int subirarchivo(FILE* poliza, PolizadeAsegurados pda[]){
  PolizadeAsegurados pa;
  int leg=0;
  fread(&pa ,sizeof(PolizadeAsegurados),1,poliza);
  while (!feof(poliza)){
         pda[leg++]=pa;
         fread(&pa ,sizeof(PolizadeAsegurados),1,poliza);
  }
return leg;
}

void ordenar( PolizadeAsegurados pa[], int tamano ){
  int i , j;
  PolizadeAsegurados aux ;
  for (i = 0 ; i < tamano ; i++ ){
       for (j = i+1 ; j < tamano ; j++ ){
            if(pa[i].cdadIncidentes < pa[j].cdadIncidentes){
               aux = pa[i];
               pa[i] = pa[j];
               pa[j] = aux ;
            }
       }
  }
return;
}

void bajararchivo(int len, FILE* poliza, PolizadeAsegurados pda[]){
  fwrite(pda, sizeof(PolizadeAsegurados), len, poliza);
  return;
}

void darDatos(){
  FILE* polizas;
  PolizadeAsegurados pa;
   cout << "_______________________________________________________________________________________________" << endl;

  polizas = fopen("asegurados.BAK","rb");
  if(polizas){
     fread(&pa ,sizeof(PolizadeAsegurados),1,polizas );
     while (!feof(polizas)){
           cout << "_______________________________________________________________________________________________" << endl;
           cout<< "Numero de poliza: "<< pa.poliza << endl;
           cout<< "¿Esta activa la poliza?  " << pa.activa <<" **1, esta activa, y 0 esta desactivada**" << endl;
           cout<< "¿La cuota esta al dia? " << pa.cuotaAlDia<< " **1, esta al dia, y si no esta al dia 0**" << endl;
           cout<< "Patente del auto: "<< pa.patenteAuto << endl;
           cout<< "Cantidad de insidentes del auto: "<< pa.cdadIncidentes << endl;
           cout<< "Nombre del cliente: "<< pa.nombre << endl;
           cout << "Apellido del cliente: "<< pa.apellido << endl;
           cout<<"DNI del cliente: "<< pa.DNI << endl;
           cout << "_______________________________________________________________________________________________" << endl;
           fread(&pa ,sizeof(PolizadeAsegurados),1,polizas );
       }
  }
  fclose(polizas);
return;
}
void guardarCambios(){
  FILE* poliza;
  FILE* polizanew;
  PolizadeAsegurados pa;
  polizanew= fopen("polizas.BAK", "wb");
  poliza= fopen("asegurados.BAK", "rb+");
  int resultado;
  if (poliza){
    while (fread (&pa,sizeof (PolizadeAsegurados),1,poliza)){
        if (pa.activa == 1){
            fwrite(&pa, sizeof(PolizadeAsegurados),1,polizanew);
        }
    }
  }
  fclose(poliza);
  fclose(polizanew);
  if (remove("asegurados.BAK")== 0){
      if(rename("polizas.BAK","asegurados.BAK") == 0)
         cout << "Los cambios se guardaron exitosamente" << endl;
      else
         cout << "No se pudo guardar los cambios" << endl;
   }

return;
}

void mostrardatos(){
  PolizadeAsegurados pda[500];
  FILE* poliza;
  poliza = fopen("asegurados.BAK","rb+");
  int len = subirarchivo(poliza, pda);
  ordenar(pda, len);
  fclose(poliza);
  poliza = fopen("asegurados.BAK","wb");
  bajararchivo(len, poliza, pda);
  fclose(poliza);
  guardarCambios();
  darDatos();
return;
}

int subir_incidentes(FILE* inci, Incidentes inc[]){
  Incidentes in;
  int longi=0;
  fread(&in ,sizeof(Incidentes),1,inci);
  while (!feof(inci)){
        inc[longi++]=in;
        fread(&in ,sizeof(Incidentes),1,inci);
  }
return longi;
}

void ponerIncidentesEnElHistorial(){
    FILE* incidente;
    FILE* procesados;
    Incidentes in;
    Incidentes pro;
    incidente= fopen("incidentes.BAK","rb");
    procesados= fopen("procesados.BAK","rb+");
    if (procesados && incidente){
        while (fread(&in,sizeof (Incidentes),1,incidente)){
               fwrite(&in, sizeof(Incidentes),1,procesados);
        }
    }
  fclose(incidente);
  fclose(procesados);
}


void procesarLoteDeIncidentes(){
  FILE* poliza;
  FILE* incidente;
  Incidentes in[500];
  Incidentes inci;
  PolizadeAsegurados pa[500];
  poliza = fopen("asegurados.BAK","rb+");
  incidente= fopen("incidentes.BAK","rb+");
  int b=subir_incidentes(incidente,in);
  int a=subirarchivo(poliza,pa);
  for (int i=0;i<a;i++){
       for(int j=0;j<b;j++){
           if (pa[i].poliza == in[j].poliza){
               pa[i].cdadIncidentes++;
           }
       }
  }
  fclose(poliza);
  fclose(incidente);
  poliza=fopen("asegurados.BAK","wb");
  bajararchivo(a,poliza,pa);
  fclose(poliza);
return;
}
void mostrar_procesados(){
  FILE* inci;
  Incidentes in;
  cout << "_______________________________________________________________________________________________" << endl;
  inci = fopen("Procesados.BAK","rb");
  if(inci){
     fread(&in ,sizeof(Incidentes),1,inci);
     while (!feof(inci)){
            cout << "_______________________________________________________________________________________________" << endl;
            cout<< "Codigo de Incidente: "<< in.codigoIncidente << endl;
            cout<< "N°Poliza: " << in.poliza << endl;
            cout<< "Fecha del Incidente: "<< in.fecha << endl;
            cout<< "Direccion del incidente: "<< in.direccion << endl;
            cout<< "Patente del auto: "<< in.patente << endl;
            cout<< "DNI del asegurado: "<< in.DNI_asegurado << endl;
            cout << "DNI de otro conductor: "<< in.DNI_otroConductor << endl;
            fread(&in ,sizeof(struct Incidentes),1,inci);
     }
  }
  fclose(inci);
return;
}

void mostrar_incidentes(){
  FILE* inci;
  Incidentes in;
  cout << "_______________________________________________________________________________________________" << endl;
  inci = fopen("incidentes.BAK","rb");
  if(inci){
     fread(&in ,sizeof(Incidentes),1,inci );
     while (!feof(inci)){
            cout << "_______________________________________________________________________________________________" << endl;
            cout<< "Codigo de Incidente: "<< in.codigoIncidente << endl;
            cout<< "N°Poliza: " << in.poliza << endl;
            cout<< "Fecha del Incidente: "<< in.fecha << endl;
            cout<< "Direccion del incidente: "<< in.direccion << endl;
            cout<< "Patente del auto: "<< in.patente << endl;
            cout<< "DNI del asegurado: "<< in.DNI_asegurado << endl;
            cout << "DNI de otro conductor: "<< in.DNI_otroConductor << endl;
            fread(&in ,sizeof(struct Incidentes),1,inci);
     }
  }
  fclose(inci);
return;
}

char menu (){
    FILE* polizas;
    PolizadeAsegurados pa;
    int tamano;
    char opcion,c;
    int nroPoliza;
    char buscarpor;
     cout<<"1. Cargar una nueva Poliza."<<endl;
     cout<<"2. Desactivar Poliza existente"<<endl;
     cout<<"3. Buscar poliza"<<endl;
     cout<<"4. mostrar datos ordenados por cantidad de incidentes"<<endl;
     cout <<"5. Procesar incidentes"<< endl;
     cout<<"6. Guardar los cambios realizados"<<endl;
     cout <<"Esc - salir"<<endl;
     do
        opcion = getch();
     while (!(opcion > '0' && opcion < '7') && (opcion != 27));
switch (opcion){
case '1':
         do{
           cargarPoliza();
           cout<< "La poliza se cargo con exito"<< endl;
           cout << "CONTINUAR ARGREGANDO POLIZAS? (S: si ; N : no) : " ;
           cin >> c; cout << endl;
           if(c == 's' || c == 'S'){
               tamano++;
           }
         }while(c!= 'n' && c!= 'N');
break;
case '2':
         cout<< "Digite el numero de poliza buscada: "<<endl;
         cin>> nroPoliza;
         desactivarPoliza(nroPoliza);
break;
case '3':
         char dniBuscado[20];
         int polizaBuscada;
         cout<< "Si poliza la va a buscar por DNI, ingrese D."<<endl;
         cout<<"Si es por numero de poliza, ingrese P"<< endl;
         cin>> buscarpor;
         if(buscarpor == 'd'|| buscarpor =='D'){
            cout<<"Ingrese el numero de DNI buscado: "<<endl;
            cin>>dniBuscado;
            busquedaPorDNI(dniBuscado);
          }
         if(buscarpor == 'p'|| buscarpor =='P'){
            cout<<"Ingrese el numero de poliza: "<<endl;
            cin>> polizaBuscada;
            busquedaPorPoliza(polizaBuscada);
         }

break;
case '4':
         mostrardatos();
break;
case '5':
         procesarLoteDeIncidentes();
         ponerIncidentesEnElHistorial();
         cout << "DESEA VER COMPLETO EL LOTE DE INCIDENTES? (S: si ; N : no) : " ;
         cin >> c; cout << endl;
         if(c == 's' || c == 'S'){
            mostrar_procesados();
         }

         // Si desea cargar incidentes al archivo para realizar las pruebas correspondientes, le dejamos programado esa parte!
         /*cout << "DESEA CARGAR UN NUEVO INCIDENTE DE FORMA MANUAL? (S: si ; N : no) : " ;
         cin >> c; cout << endl;
         if(c == 's' || c == 'S'){
            cargarIncidente();
            cout<< "El incidente a se cargo con exito"<< endl;
         }
         cout << "DESEA CARGAR UN PROCESADO DE FORMA MANUAL? (S: si ; N : no) : " ;
         cin >> c; cout << endl;
         if(c == 's' || c == 'S'){
            cargarProcesados();
            cout<< "El procesado a se cargo con exito"<< endl;
         }*/
break;
case '6':
         guardarCambios();
         cout<<"Fin de la jornada!"<< endl;
break;
}
return opcion;
}

int main()
{
  char i;
  do
    i = menu();
  while (i != 27);

return 0;
}
