// tienda.c - Versión corregida y mejorada del sistema WhiskerPets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Prototipos
void administrador();
void añadirUsuario();
void añadirProducto();
void modificarProducto();
void eliminarProducto();
void modificarUsuario();
void eliminarUsuario();
void modificarDineroUsuario();
void modificarCostoProducto();
void mostrarTicketEnTerminal();
char *strrstr(const char *haystack, const char *needle);
void menuCliente(char usuario[], float dineroDisponible);
void usuario();
void comprarProducto(char usuario[], float *dineroDisponible);
void guardarDineroUsuario(const char usuario[], float dineroNuevo);
void generarTicket(const char usuario[], const char producto[], int cantidad, float precioUnitario, float total);
void mostrarProductos();

void agregarCupon();
float usarCupon(float total);

// Util
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Variables globales
int opcion;

int main() {
    do {
        printf("________________________________ \n");
        printf("║       WHISKERPETS            ║ \n\n");
        printf("           /\\___/\\\n");
        printf("          (  o o  )\n");
        printf("          /   ^   \\\n");
        printf("         /  |   |  \\\n");
        printf("        (   |___|   )\n");
        printf("         \\__|   |__/\n");
        printf("1. Administrador\n");
        printf("2. Compra (Cliente)\n");
        printf("3. Contactar programador\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            limpiarBuffer();
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1:
                administrador();
                break;
            case 2:
                usuario();
                break;
            case 3:
                printf("Contacte al programador al correo: ianrosaswhiskertpets@gmail.com\n");
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);

    return 0;
}

/* ---------------- ADMINISTRADOR ---------------- */
void administrador() {
    char user[64], pass[64];
    char archivoUser[64], archivoPass[64];
    int intentos = 0;
    FILE *f;

    f = fopen("admin.txt", "r");
    if (f == NULL) {
        printf("ERROR: No se encontro el archivo admin.txt\n");
        return;
    }

    if (fscanf(f, "%63s %63s", archivoUser, archivoPass) != 2) {
        fclose(f);
        printf("ERROR: admin.txt con formato incorrecto\n");
        return;
    }
    fclose(f);

    do {
        printf("\n--- Inicio Administrador ---\n");
        printf("Usuario: ");
        scanf("%63s", user);
        printf("Contrasena: ");
        scanf("%63s", pass);

        if (strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            printf("\n✔ Acceso concedido.\n");
            break;
        } else {
            printf("\nUsuario o contrasena incorrectos.\n");
            intentos++;
        }

        if (intentos == 3) {
            printf("\nRegresando al menú principal...\n");
            return;
        }

    } while (intentos < 3);

    int opc;
    do {
        printf("\n----- MENU ADMIN  -----\n");
        printf(" /\\_/\\\n");
        printf("( [o.o] )\n");
        printf("  > ^ <\n");
        printf("1. Añadir Usuario\n");
        printf("2. Modificar Usuario\n");
        printf("3. Eliminar Usuario\n");
        printf("4. Añadir Producto\n");
        printf("5. Modificar Producto\n");
        printf("6. Eliminar Producto\n");
        printf("7. Modificar Dinero de Usuario\n");
        printf("8. Modificar Costo de Producto\n");
        printf("9. Agregar cupon de descuento\n");
        printf("10. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opc) != 1) { limpiarBuffer(); opc = 0; }

        switch (opc) {
            case 1: añadirUsuario(); break;
            case 2: modificarUsuario(); break;
            case 3: eliminarUsuario(); break;
            case 4: añadirProducto(); break;
            case 5: modificarProducto(); break;
            case 6: eliminarProducto(); break;
            case 7: modificarDineroUsuario(); break;
            case 8: modificarCostoProducto(); break;
            case 9: agregarCupon(); break;
            case 10: printf("Saliendo del administrador...\n"); break;
            default: if (opc!=0) printf("Opción no valida.\n");
        }

    } while (opc != 10);
}

/* ---------------- USUARIOS ---------------- */
void añadirUsuario() {
    FILE *f;
    char user[64], pass[64];
    float dinero;

    printf("\n--- Añadir Nuevo Usuario ---\n");
    printf("Usuario nuevo: ");
    scanf("%63s", user);
    printf("Contraseña: ");
    scanf("%63s", pass);
    printf("Dinero inicial: ");
    if (scanf("%f", &dinero) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); return; }

    f = fopen("clientes.txt", "a");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir clientes.txt\n");
        return;
    }
    fprintf(f, "%s %s %.2f\n", user, pass, dinero);
    fclose(f);
    printf("Usuario agregado correctamente.\n");
}

void eliminarUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[64];
    char user[64], pass[64];
    float dinero;
    int encontrado = 0;

    printf("\n--- Eliminar Usuario ---\n");
    printf("Ingrese el usuario que desea eliminar: ");
    scanf("%63s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %63s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;
            continue;
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (encontrado) printf("\n✔ Usuario eliminado correctamente.\n");
    else printf("\nUsuario no encontrado.\n");
}

void modificarUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[64];
    char user[64], pass[64];
    float dinero;
    int encontrado = 0;

    printf("\n--- Modificar Usuario ---\n");
    printf("Ingrese el usuario que desea modificar: ");
    scanf("%63s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %63s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;
            printf("\n✔ Usuario encontrado.\n");
            printf("usuario: %s\n", user);
            printf("contraseña: %s\n", pass);
            printf("dinero: $%.2f\n\n", dinero);

            printf("Ingrese los nuevos datos:\n");
            printf("Nuevo usuario: ");
            scanf("%63s", user);
            printf("Nueva contraseña: ");
            scanf("%63s", pass);
            printf("Nuevo dinero ($): ");
            if (scanf("%f", &dinero) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); }
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (encontrado) printf("\n✔ Usuario modificado correctamente.\n");
    else printf("\nUsuario no encontrado.\n");
}

/* ---------------- PRODUCTOS ---------------- */
void añadirProducto() {
    FILE *f;
    char nombre[64];
    float precio;
    int stock;

    printf("\n--- Añadir Producto ---\n");
    printf("Nombre del producto (sin espacios): ");
    scanf("%63s", nombre);
    printf("Precio: ");
    if (scanf("%f", &precio) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); return; }
    printf("Stock (existencias): ");
    if (scanf("%d", &stock) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); return; }

    f = fopen("productos.txt", "a");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir productos.txt\n");
        return;
    }

    // Nuevo formato: nombre precio stock
    fprintf(f, "%s %.2f %d\n", nombre, precio, stock);
    fclose(f);

    printf("Producto agregado correctamente.\n");
}

void mostrarProductos() {
    FILE *f;
    char nombre[64];
    float precio;
    int stock;

    f = fopen("productos.txt", "r");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir productos.txt\n");
        return;
    }

    printf("\n--- PRODUCTOS DISPONIBLES ---\n");
    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        printf("Producto: %s | Precio: $%.2f | Stock: %d\n", nombre, precio, stock);
    }

    fclose(f);
}

void modificarProducto() {
    FILE *f, *temp;
    char productoBuscado[64];
    char nombre[64];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Modificar Producto ---\n");
    printf("Ingrese el nombre del producto que desea modificar: ");
    scanf("%63s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;
            printf("\n✔ Producto encontrado.\n");
            printf("Nombre: %s\n", nombre);
            printf("Precio: $%.2f\n", precio);
            printf("Existencias: %d\n\n", stock);

            printf("Ingrese los nuevos datos:\n");
            printf("Nuevo nombre: ");
            scanf("%63s", nombre);
            printf("Nuevo precio ($): ");
            if (scanf("%f", &precio) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); }
            printf("Nuevas existencias: ");
            if (scanf("%d", &stock) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); }
        }
        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (encontrado) printf("\n✔ Producto modificado correctamente.\n");
    else printf("\nProducto no encontrado.\n");
}

void eliminarProducto() {
    FILE *f, *temp;
    char productoBuscado[64];
    char nombre[64];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Eliminar Producto ---\n");
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%63s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;
            printf("\n✔ Producto encontrado.\n");
            printf("Nombre: %s\n", nombre);
            printf("Precio: $%.2f\n", precio);
            printf("Existencias: %d\n", stock);
            char confirmacion;
            printf("\n¿Seguro que quiere eliminar este producto? (s/n): ");
            scanf(" %c", &confirmacion);
            if (confirmacion == 's' || confirmacion == 'S') {
                printf("\n✔ Producto eliminado correctamente.\n");
                continue; // no lo copiamos
            } else {
                printf("\n Eliminación cancelada por el usuario.\n");
                // se copia normalmente
            }
        }
        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (!encontrado) printf("\nProducto no encontrado.\n");
}

void modificarCostoProducto() {
    FILE *f, *temp;
    char productoBuscado[64];
    char nombre[64];
    float precio;
    int stock;
    int encontrado = 0;

    printf("\n--- Modificar Costo de Producto ---\n");
    printf("Ingrese el nombre del producto: ");
    scanf("%63s", productoBuscado);

    f = fopen("productos.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR al abrir archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, productoBuscado) == 0) {
            encontrado = 1;
            printf("\n✔ Producto encontrado.\n");
            printf("Costo actual: $%.2f\n", precio);
            printf("Nuevo costo: $");
            if (scanf("%f", &precio) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); }
        }
        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    if (encontrado) printf("\n✔ Costo modificado correctamente.\n");
    else printf("\nProducto no encontrado.\n");
}

/* ---------------- DINERO USUARIO ---------------- */
void modificarDineroUsuario() {
    FILE *f, *temp;
    char usuarioBuscado[64];
    char user[64], pass[64];
    float dinero;
    int encontrado = 0;

    printf("\n--- Modificar Dinero del Usuario ---\n");
    printf("Ingrese el nombre del usuario: ");
    scanf("%63s", usuarioBuscado);

    f = fopen("clientes.txt", "r");
    temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("ERROR al abrir archivo.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %63s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuarioBuscado) == 0) {
            encontrado = 1;
            printf("\n✔ Usuario encontrado.\n");
            printf("Dinero actual: $%.2f\n", dinero);
            printf("Nuevo dinero: $");
            if (scanf("%f", &dinero) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); }
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (encontrado) printf("\nDinero modificado correctamente. MIAU\n");
    else printf("\nUsuario no encontrado.\n");
}

/* ---------------- SESION USUARIO ---------------- */
void usuario() {
    char user[64], pass[64];
    char archivoUser[64], archivoPass[64];
    float dineroDisponible;
    int encontrado = 0;

    FILE *f = fopen("clientes.txt", "r");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir clientes.txt\n");
        return;
    }

    printf("\n--- INICIO DE SESION CLIENTE ---\n");
    printf("Usuario: ");
    scanf("%63s", user);
    printf("Contrasena: ");
    scanf("%63s", pass);

    while (fscanf(f, "%63s %63s %f", archivoUser, archivoPass, &dineroDisponible) == 3) {
        if (strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("\nUsuario o contrasena incorrectos.\nRegresando al menú principal...\n");
        return;
    }

    printf("\n✔ Bienvenido %s\n", user);
    printf("Saldo disponible: $%.2f\n\n", dineroDisponible);

    menuCliente(user, dineroDisponible);
}

void menuCliente(char usuario[], float dineroDisponible) {
    int opc;
    float montoRecarga;

    do {
        printf("\n------ MENU CLIENTE ------\n");
        printf("1. Ver productos\n");
        printf("2. Comprar productos\n");
        printf("3. Recargar dinero\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opc) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); opc = 0; }

        switch (opc) {
            case 1: mostrarProductos(); break;
            case 2: comprarProducto(usuario, &dineroDisponible); break;
            case 3:
                printf("\nIngrese la cantidad a recargar: $");
                if (scanf("%f", &montoRecarga) != 1) {
                    printf("Entrada invalida.\n");
                    limpiarBuffer();
                    break;
                }
                if (montoRecarga <= 0) {
                    printf("Monto invalido.\n");
                    break;
                }
                dineroDisponible += montoRecarga;
                guardarDineroUsuario(usuario, dineroDisponible);
                printf("Recarga exitosa. Nuevo saldo: $%.2f\n", dineroDisponible);
                break;
            case 4: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opc != 4);
}

/* ---------------- GUARDAR SALDO ---------------- */
void guardarDineroUsuario(const char usuario[], float dineroNuevo) {
    FILE *f = fopen("clientes.txt", "r");
    if (!f) { printf("Error: clientes.txt no existe.\n"); return; }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) { printf("Error: no se pudo crear temp.txt\n"); fclose(f); return; }

    char user[64], pass[64];
    float dinero;
    int encontrado = 0;

    while (fscanf(f, "%63s %63s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuario) == 0) {
            dinero = dineroNuevo;
            encontrado = 1;
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    if (encontrado) {
        remove("clientes.txt");
        rename("temp.txt", "clientes.txt");
    } else {
        printf("Error: usuario no encontrado, NO se modificó clientes.txt.\n");
        remove("temp.txt");
    }
}

/* ---------------- COMPRAR PRODUCTO ---------------- */
void comprarProducto(char usuario[], float *dineroDisponible) {
    char producto[64], nombre[64];
    float precio;
    int stock, cantidad;
    int encontrado = 0;
    FILE *f = NULL, *temp = NULL;

    mostrarProductos();

    printf("\nIngrese el nombre del producto que desea comprar: ");
    scanf("%63s", producto);

    f = fopen("productos.txt", "r");
    if (!f) { printf("Error: no se pudo abrir productos.txt\n"); return; }
    temp = fopen("temp.txt", "w");
    if (!temp) { printf("Error: no se pudo crear archivo temporal.\n"); fclose(f); return; }

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, producto) == 0) {
            encontrado = 1;
            printf("Cuantos desea comprar? ");
            if (scanf("%d", &cantidad) != 1) {
                printf("Cantidad invalida.\n");
                limpiarBuffer();
                // copiar registro sin cambios
                fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
                continue;
            }

            if (cantidad > stock) {
                printf("\nNo hay suficientes existencias. Stock disponible: %d\n", stock);
                // escribir registro sin cambiar
                fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
                continue;
            }

            float total = precio * cantidad;
            // aplicar cupon si el usuario tiene uno
            total = usarCupon(total);

            if (total > *dineroDisponible) {
                printf("\nNo tiene suficiente dinero.\n");
                printf("Faltan: $%.2f\n", total - *dineroDisponible);
                // escribimos el registro sin modificar
                fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
                continue;
            }

            // compra exitosa: actualizar dinero y stock
            *dineroDisponible -= total;
            stock -= cantidad;

            printf("\nCompra realizada con exito.\n");
            generarTicket(usuario, producto, cantidad, precio, total);

            // persistir nuevo saldo del usuario en archivo clientes
            guardarDineroUsuario(usuario, *dineroDisponible);

            // escribir producto con stock actualizado
            fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
            continue;
        }

        // registro no afectado
        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    if (encontrado) {
        remove("productos.txt");
        rename("temp.txt", "productos.txt");
    } else {
        printf("\nProducto no encontrado.\n");
        remove("temp.txt");
    }
}

/* ---------------- TICKET ---------------- */
void generarTicket(const char usuario[], const char producto[], int cantidad, float precioUnitario, float total) {
    FILE *t;
    time_t ahora;
    time(&ahora);

    t = fopen("ticket.txt", "a");
    if (t == NULL) {
        printf("ERROR: No se pudo crear ticket.txt\n");
        return;
    }

    // Separador único para poder localizar el último ticket
    fprintf(t, "###TICKET-START###\n");
    fprintf(t, "Cliente: %s\n", usuario);
    fprintf(t, "Fecha: %s", ctime(&ahora));
    fprintf(t, "Producto: %s\n", producto);
    fprintf(t, "Cantidad: %d\n", cantidad);
    fprintf(t, "Precio unitario: $%.2f\n", precioUnitario);
    fprintf(t, "Total pagado: $%.2f\n", total);
    fprintf(t, "###TICKET-END###\n\n");

    fclose(t);

    printf("\nTicket generado correctamente (ticket.txt)\n");

    // Mostrar solo el ultimo ticket
    mostrarTicketEnTerminal();
}

void mostrarTicketEnTerminal() {
    FILE *t = fopen("ticket.txt", "r");
    if (t == NULL) {
        printf("No se encontro el archivo ticket.txt\n");
        return;
    }

    // Leemos todo el archivo en memoria (prudente si no es muy grande)
    fseek(t, 0, SEEK_END);
    long size = ftell(t);
    fseek(t, 0, SEEK_SET);

    char *buf = malloc(size + 1);
    if (!buf) { fclose(t); printf("Error de memoria al leer ticket.\n"); return; }

    fread(buf, 1, size, t);
    buf[size] = '\0';
    fclose(t);

    // Buscar el último bloque entre ###TICKET-START### y ###TICKET-END###
    char *start = strstr(buf, "###TICKET-START###");
    if (!start) {
        printf("No hay tickets para mostrar.\n");
        free(buf);
        return;
    }
    char *end = strstr(start, "###TICKET-END###");
    if (!end) {
        printf("Ticket corrupto (no se encontro fin del ticket).\n");
        free(buf);
        return;
    }
    end += strlen("###TICKET-END###");

    printf("\n===== ULTIMO TICKET =====\n");
    // imprimir desde start hasta end
    fwrite(start, 1, end - start, stdout);
    printf("\n=========================\n\n");

    free(buf);
}

// helper: strrstr (buscar la ultima ocurrencia de una subcadena)
char *strrstr(const char *haystack, const char *needle) {
    char *last = NULL;
    char *p;

    if (!*needle) {
        return (char *)haystack + strlen(haystack);
    }

    p = strstr(haystack, needle);

    while (p != NULL) {
        last = p;
        p = strstr(p + 1, needle);
    }

    return last;
}


/* ---------------- CUPONES ---------------- */
void agregarCupon(){
    FILE *f = fopen("cupones.txt", "a");
    if (!f) {
        printf("Error al abrir cupones.txt\n");
        return;
    }

    char codigo[64];
    int descuento;

    printf("Ingrese el codigo del cupon: ");
    scanf("%63s", codigo);
    printf("Ingrese el porcentaje de descuento (1-100): ");
    if (scanf("%d", &descuento) != 1) { printf("Entrada invalida.\n"); limpiarBuffer(); fclose(f); return; }

    if (descuento < 1 || descuento > 100) {
        printf("Descuento invalido.\n");
        fclose(f);
        return;
    }

    fprintf(f, "%s %d\n", codigo, descuento);
    fclose(f);
    printf("\nCupon agregado correctamente!\n");
}

float usarCupon(float total) {
    FILE *f = fopen("cupones.txt", "r");
    if (!f) {
        // no hay cupones
        return total;
    }

    printf("¿Tiene algún cupón? (s/n): ");
    char op;
    scanf(" %c", &op);
    if (op == 'n' || op == 'N') { fclose(f); return total; }

    char codigoIngresado[64];
    printf("Ingrese el código del cupón: ");
    scanf("%63s", codigoIngresado);

    // Buscamos el cupón y lo removemos (cupón de un solo uso)
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) { printf("Error interno (temp).\n"); fclose(f); return total; }

    char codigo[64];
    int descuento;
    int encontrado = 0;
    float totalFinal = total;

    while (fscanf(f, "%63s %d", codigo, &descuento) == 2) {
        if (!encontrado && strcmp(codigo, codigoIngresado) == 0) {
            // aplicar descuento y NO copiar este cupon a temp -> lo consumimos
            encontrado = 1;
            float rebaja = total * (descuento / 100.0f);
            totalFinal = total - rebaja;
            printf("\n✔ Cupón válido (%d%% de descuento)\n", descuento);
            printf("Descuento aplicado: -$%.2f\n", rebaja);
            printf("Nuevo total: $%.2f\n", totalFinal);
            continue;
        }
        // copiar cupones no usados / que no coinciden
        fprintf(temp, "%s %d\n", codigo, descuento);
    }
    fclose(f);
    fclose(temp);

    remove("cupones.txt");
    rename("temp.txt", "cupones.txt");

    if (!encontrado) {
        printf("\nCupón no encontrado o inválido.\n");
        return total;
    }

    return totalFinal;
}