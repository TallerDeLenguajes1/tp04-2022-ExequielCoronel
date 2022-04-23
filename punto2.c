#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
};

typedef struct Tarea ListaTask;

void cargarTareas(ListaTask **Tareas, int cantidadTask);
void mostrarTareas(ListaTask **Tareas, int cantidadTask);
void marcarTareasRealizadas(ListaTask **TareasPendientes, ListaTask **TareasRealizadas, int cantidadTask);
struct Tarea *BusquedaPorPalabra(ListaTask **Tareas, char *PalabraClave, int cantidadTask);
void mostrarTarea(struct Tarea *tarea);

void main (){
    int cantidadTask;
    ListaTask **TareasPendientes, **TareasRealizadas, *tarea;
    srand(time(NULL));
    printf("Ingrese la cantidad de tareas que desea cargar: ");
    scanf("%d", &cantidadTask);
    fflush(stdin);
    TareasPendientes = (ListaTask **)malloc(sizeof(ListaTask *)*cantidadTask);
    TareasRealizadas = (ListaTask **)malloc(sizeof(ListaTask *)*cantidadTask);
    cargarTareas(TareasPendientes, cantidadTask);
    marcarTareasRealizadas(TareasPendientes, TareasRealizadas, cantidadTask);
    printf("Tareas Realizadas: \n");
    mostrarTareas(TareasRealizadas, cantidadTask);
    printf("Tareas Pendientes: \n");
    mostrarTareas(TareasPendientes, cantidadTask);
    tarea = BuscarPorPalabra(TareasPendientes,"Comer",cantidadTask);
    mostrarTarea(tarea);
}

void cargarTareas(ListaTask **Tareas, int cantidadTask){
    char *BuffDescripcion;
    BuffDescripcion = (char *)malloc(300);
    for (int i = 0; i < cantidadTask; i++)
    {
        Tareas[i] = (ListaTask *)malloc(sizeof(ListaTask));
        printf("\n\tTarea %d: \n", i+1);
        Tareas[i]->TareaID = i+1;
        printf("Ingrese la descirpcion de la tarea: ");
        gets(BuffDescripcion);
        Tareas[i]->Descripcion = (char *)malloc((strlen(BuffDescripcion)+1)*sizeof(char));
        strcpy(Tareas[i]->Descripcion, BuffDescripcion);
        Tareas[i]->Duracion = rand () % 91 + 10;
    }
    free(BuffDescripcion);
}

void marcarTareasRealizadas(ListaTask **TareasPendientes, ListaTask **TareasRealizadas, int cantidadTask){
    int marca;
    for(int i = 0;i<cantidadTask;i++)
    {
        printf("\n------------ID tarea: %d------------------\n",TareasPendientes[i]->TareaID);
        printf("Descripcion de la tarea: \n");
        puts(TareasPendientes[i]->Descripcion);
        printf("Duracion: %dmin\n\n", TareasPendientes[i]->Duracion);
        printf("%cRealizo esta tarea? 1=Si, 0=No: ",168);
        do{
            scanf("%d",&marca);
            fflush(stdin);
            if(marca!=0 && marca!=1){
                printf("\nSolo es posible ingresar 1 o 0, 1=Si, 0=No\n");
            }
        }while(marca!=0 && marca!=1);
        printf("------------------------------------------\n");
        if(marca == 1){
            TareasRealizadas[i] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
        } else {
            TareasRealizadas[i] = NULL;
        }
    }
}

void mostrarTareas(ListaTask **Tareas, int cantidadTask){
    for(int i = 0; i<cantidadTask; i++)
    {
        if(Tareas[i]!=NULL){
            printf("\nID de la Tarea %d\n", Tareas[i]->TareaID);
            printf("Descripcion de la tarea: ");
            puts(Tareas[i]->Descripcion);
            printf("Duracion: %dmin\n\n", Tareas[i]->Duracion);
        }
    }
}

struct Tarea *BusquedaPorPalabra(ListaTask **Tareas, char *PalabraClave, int cantidadTask){
    for(int i=0;i<cantidadTask;i++)
    {
        if(strcmp(Tareas[i]->Descripcion,PalabraClave)==0){
            printf("\nTarea encontrada!\n");
            return(Tareas[i]);
        }
    }
    printf("\nNo encontrada! :c");
    return NULL;
}

void mostrarTarea(struct Tarea *tarea){
    printf("ID Tarea: %d",tarea->TareaID);
    printf("\nDescripcion: ");
    puts(tarea->Descripcion);
    printf("Duracion: %dmin",tarea->Duracion);
}

