//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//Funciones del administrador
void administrador();
void añadirUsuario();
void añadirProducto();
void modificarProducto();
void eliminarProducto();
void modificarUsuario();
void eliminarUsuario();
void modificarDineroUsuario();
void modificarCostaProducto();
//Funciones de usuario
void usuario();
int comprarProducto();
int recargarDinero();
int totalCompra();
int agregarProducto();
//Variables globales
int opcion;
//variables struct
//MENU PRINCIPAL
int main(){
    do{
    printf("******* WHISKERPETS *******\n");
    printf("1. Administrador\n");
    printf("2. compra\n");
    printf("3.-Conatactar programador\n");
    printf("4.-Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d",&opcion);
        switch(opcion){
            case 1:
                administrador();
                break;
            case 2:
                usuario();
                break;
            case 3:
                printf("Contacte al programador al correo: ");
        }
    } while(opcion!=1);
    return 0;
}

