// tienda.c - Sistema WhiskerPets (versión corregida y parchada)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ================== PROTOTIPOS ==================

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
void mostrarPlanes();

void menuCliente(char usuario[], float dinero, char plan[]);
void usuario();
void comprarProducto(char usuario[], float *dineroDisponible);
void guardarDineroUsuario(const char usuario[], float dineroNuevo);
void generarTicket(const char usuario[], const char producto[], int cantidad, float precioUnitario, float total);
void mostrarProductos();

void agregarCupon();
float usarCupon(float total);
float aplicarDescuentoPlan(float total, char plan[]);
void generarCuponPorPlan(char plan[]);
void elegirPlan(char plan[]);

// Prototipo necesario
char *strrstr(const char *haystack, const char *needle);

// ================== UTIL ==================

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// ================== VARIABLES GLOBALES ==================
int opcion;

// ================== MAIN ==================

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
            case 1: administrador(); break;
            case 2: usuario(); break;
            case 3:
                printf("Contacte al programador al correo: Ojeda Falcon Mario Leonel\n");
                printf("\t Ian Michel Rosas");
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    return 0;
}

// ================== ADMINISTRADOR ==================

void administrador() {
    char user[64], pass[64];
    char archivoUser[64], archivoPass[64];
    int intentos = 0;
    FILE *f;

    f = fopen("admin.txt", "r");
    if (f == NULL) {
        printf("ERROR: No se encontró el archivo admin.txt\n");
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
        printf("Contraseña: ");
        scanf("%63s", pass);

        if (strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            printf("\n✔ Acceso concedido.\n");
            break;
        } else {
            printf("\nUsuario o contraseña incorrectos.\n");
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
        printf("Seleccione una opción: ");
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
            default: if (opc != 0) printf("Opción no válida.\n");
        }

    } while (opc != 10);
}

// ================== USUARIOS ==================

void añadirUsuario()
{
    FILE *f;
    char user[64], pass[64];
    float dinero;
    char plan[16];

    printf("\n--- Añadir Usuario ---\n");

    printf("Usuario: ");
    scanf("%63s", user);

    printf("Contraseña: ");
    scanf("%63s", pass);

    printf("Dinero inicial: $");
    scanf("%f", &dinero);

    elegirPlan(plan);

    f = fopen("clientes.txt", "a");
    if (!f)
    {
        printf("ERROR al abrir clientes.txt\n");
        return;
    }

    fprintf(f, "%s %s %.2f %s\n", user, pass, dinero, plan);
    fclose(f);

    printf("\n✔ Usuario creado con plan %s\n", plan);
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
    temp = fopen("clientes_tmp.txt", "w");
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
    rename("clientes_tmp.txt", "clientes.txt");

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
    temp = fopen("clientes_tmp.txt", "w");
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
            if (scanf("%f", &dinero) != 1) { printf("Entrada inválida.\n"); limpiarBuffer(); }
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("clientes_tmp.txt", "clientes.txt");

    if (encontrado) printf("\n✔ Usuario modificado correctamente.\n");
    else printf("\nUsuario no encontrado.\n");
}

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
    temp = fopen("clientes_tmp.txt", "w");
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
    rename("clientes_tmp.txt", "clientes.txt");

    if (encontrado) printf("\nDinero modificado correctamente. MIAU\n");
    else printf("\nUsuario no encontrado.\n");
}
// ================== PRODUCTOS ==================

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

    fprintf(f, "%s %.2f %d\n", nombre, precio, stock);
    fclose(f);

    printf("Producto agregado correctamente.\n");
}

void mostrarProductos()
{
    FILE *f = fopen("productos.txt", "r");

    if (f == NULL) {
        printf("\nNo hay productos cargados.\n");
        return;
    }

    char nombre[64];
    float precio;
    int stock;

    int hayProductos = 0;

    printf("\n--- PRODUCTOS EN STOCK ---\n");

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        printf("Producto: %-15s | Precio: $%6.2f | Stock: %d\n", nombre, precio, stock);
        hayProductos = 1;
    }

    fclose(f);

    if (!hayProductos)
        printf("No hay productos disponibles.\n");
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
    temp = fopen("productos_tmp.txt", "w");
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
    rename("productos_tmp.txt", "productos.txt");

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
    temp = fopen("productos_tmp.txt", "w");
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
                continue;
            } else {
                printf("\n Eliminación cancelada por el usuario.\n");
            }
        }
        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt");

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
    temp = fopen("productos_tmp.txt", "w");
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
    rename("productos_tmp.txt", "productos.txt");

    if (encontrado) printf("\n✔ Costo modificado correctamente.\n");
    else printf("\nProducto no encontrado.\n");
}

// ================== USUARIO Y COMPRAS ==================

void usuario() {
    FILE *f;
    char user[64], pass[64];
    char archivoUser[64], archivoPass[64];
    char plan[16];
    float dinero;
    int encontrado = 0;

    printf("\n--- Inicio de Sesión Cliente ---\n");

    printf("Usuario: ");
    scanf("%63s", user);
    printf("Contraseña: ");
    scanf("%63s", pass);

    f = fopen("clientes.txt", "r");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir clientes.txt\n");
        return;
    }

    while (fscanf(f, "%63s %63s %f %15s", archivoUser, archivoPass, &dinero, plan) == 4) {
        if (strcmp(user, archivoUser) == 0 && strcmp(pass, archivoPass) == 0) {
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("Usuario o contraseña incorrectos.\n");
        return;
    }

    printf("\n✔ Bienvenido, %s!\n", user);
    printf("Dinero disponible: $%.2f\n", dinero);
    printf("Plan actual: %s\n\n", plan);
    menuCliente(user, dinero, plan);
}


void menuCliente(char usuario[], float dinero, char plan[]) {
    int opc;

    do {
        printf("\n----- MENU CLIENTE -----\n");
        printf("Dinero actual: $%.2f\n", dinero);
        printf("Plan actual: %s\n", plan);
        printf("1. Mostrar productos\n");
        printf("2. Comprar producto\n");
        printf("3. Ver último ticket\n");
        printf("4. Mostrar planes\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opc) != 1) { limpiarBuffer(); opc = 0; }

        switch (opc) {
            case 1:
                mostrarProductos();
                break;

            case 2:
                comprarProducto(usuario, &dinero);
                break;

            case 3:
                mostrarTicketEnTerminal();
                break;

            case 4:
                mostrarPlanes();
                break;
            case 5:
                printf("Saliendo del menú cliente...\n");
                guardarDineroUsuario(usuario, dinero);
                break;
            default:
                printf("Opción no válida.\n");
        }

    } while (opc != 4);
}

void guardarDineroUsuario(const char usuario[], float dineroNuevo) {
    FILE *f, *temp;
    char user[64], pass[64];
    float dinero;

    f = fopen("clientes.txt", "r");
    temp = fopen("clientes_tmp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("ERROR guardando dinero.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fscanf(f, "%63s %63s %f", user, pass, &dinero) == 3) {
        if (strcmp(user, usuario) == 0) {
            dinero = dineroNuevo;
        }
        fprintf(temp, "%s %s %.2f\n", user, pass, dinero);
    }

    fclose(f);
    fclose(temp);

    remove("clientes.txt");
    rename("clientes_tmp.txt", "clientes.txt");

    printf("\n✔ Dinero actualizado.\n");
}

void comprarProducto(char usuario[], float *dineroDisponible)
{
    FILE *f = fopen("productos.txt", "r");
    FILE *temp = fopen("productos_tmp.txt", "w");
    char plan[16];
    if (!f || !temp) {
        printf("ERROR al abrir productos.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char productoBuscado[64];
    char nombre[64];
    float precio;
    int stock;
    int cantidad;
    float total;

    int encontrado = 0;
    int compraExitosa = 0;

    mostrarProductos();

    printf("\nIngrese el nombre del producto que desea comprar: ");
    scanf("%63s", productoBuscado);

    while (fscanf(f, "%63s %f %d", nombre, &precio, &stock) == 3) {
        if (strcmp(nombre, productoBuscado) == 0 && !encontrado) {

            encontrado = 1;

            printf("\n✔ Producto encontrado.\n");
            printf("Precio: $%.2f\nStock disponible: %d\n", precio, stock);

            printf("Cantidad a comprar: ");
            if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                printf("Cantidad inválida.\n");
            }
            else if (cantidad > stock) {
                printf("No hay suficiente stock.\n");
            }
            else {
                total = precio * cantidad;

                printf("\nSubtotal: $%.2f\n", total);

                total = usarCupon(total);

                total = aplicarDescuentoPlan(total, plan);
                printf("Total con plan %s: $%.2f\n", plan, total);


                if (*dineroDisponible >= total) {

                    *dineroDisponible -= total;
                    stock -= cantidad;

                    generarTicket(
                        usuario,
                        nombre,
                        cantidad,
                        precio,
                        total
                    );

                    printf("\n✔ Compra realizada con éxito.\n");
                    compraExitosa = 1;
                }
                else {
                    printf("\nDinero insuficiente. Compra cancelada.\n");
                }
            }
        }

        fprintf(temp, "%s %.2f %d\n", nombre, precio, stock);
    }

    fclose(f);
    fclose(temp);

    remove("productos.txt");
    rename("productos_tmp.txt", "productos.txt");

    if (!encontrado)
        printf("\nProducto no encontrado.\n");

    if (!compraExitosa && encontrado)
        printf("\nNo se efectuó la compra.\n");
}

// ================== TICKETS ==================

void generarTicket(const char usuario[], const char producto[], int cantidad, float precioUnitario, float total) {
    FILE *t;
    time_t ahora;
    time(&ahora);

    t = fopen("ticket.txt", "a");
    if (!t) {
        printf("ERROR: No se pudo crear ticket.txt\n");
        return;
    }

     fprintf(t, "=====================================\n");
    fprintf(t, "          TICKET DE COMPRA\n");
    fprintf(t, "=====================================\n");
    fprintf(t, "Cliente: %s\n", usuario);
    fprintf(t, "Fecha: %s", ctime(&ahora)); // Fecha y hora automática
    fprintf(t, "-------------------------------------\n");
    fprintf(t, "Producto: %s\n", producto);
    fprintf(t, "Cantidad: %d\n", cantidad);
    fprintf(t, "Precio unitario: $%.2f\n", precioUnitario);
    fprintf(t, "Total pagado: $%.2f\n", total);
    fprintf(t, "-------------------------------------\n");
    fprintf(t, " ¡Gracias por su compra! WOF WOF\n");
    fprintf(t, "=====================================\n\n");

    fclose(t);

    printf("\n✔ Ticket generado correctamente.\n");
}

void mostrarTicketEnTerminal() {
    FILE *t = fopen("ticket.txt", "r");
    if (!t) {
        printf("No se encontró el archivo ticket.txt\n");
        return;
    }

    fseek(t, 0, SEEK_END);
    long size = ftell(t);
    fseek(t, 0, SEEK_SET);

    char *buf = malloc(size + 1);
    if (!buf) { fclose(t); printf("Error de memoria.\n"); return; }

    fread(buf, 1, size, t);
    buf[size] = '\0';
    fclose(t);

    char *start = strrstr(buf, "=====================================\n");
    if (!start) {
        printf("No hay tickets para mostrar.\n");
        free(buf);
        return;
    }
    char *end = strstr(start, "=====================================\n");
    if (!end) {
        printf("Ticket corrupto.\n");
        free(buf);
        return;
    }
    end += strlen("");

    printf("\n===== ÚLTIMO TICKET =====\n");
    fwrite(start, 1, end - start, stdout);
    printf("\n=========================\n\n");

    free(buf);
}

char *strrstr(const char *haystack, const char *needle) {
    char *result = NULL;
    char *p;
    if (!*needle) return (char *)haystack + strlen(haystack);
    p = strstr(haystack, needle);
    while (p != NULL) {
        result = p;
        p = strstr(p + 1, needle);
    }
    return result;
}

// ================== CUPONES ==================

void agregarCupon() {
    FILE *f = fopen("cupones.txt", "a");
    if (!f) { printf("Error al abrir cupones.txt\n"); return; }

    char codigo[64];
    int descuento;

    printf("Ingrese el código del cupón: ");
    scanf("%63s", codigo);
    printf("Ingrese el porcentaje de descuento (1-100): ");
    if (scanf("%d", &descuento) != 1) { printf("Entrada inválida.\n"); limpiarBuffer(); fclose(f); return; }

    if (descuento < 1 || descuento > 100) {
        printf("Descuento inválido.\n");
        fclose(f);
        return;
    }

    fprintf(f, "%s %d\n", codigo, descuento);
    fclose(f);
    printf("✔ Cupón agregado correctamente.\n");
}

float usarCupon(float total) {
    FILE *f = fopen("cupones.txt", "r");
    if (!f) return total;

    printf("¿Tiene algún cupón? (s/n): ");
    char op;
    scanf(" %c", &op);
    if (op == 'n' || op == 'N') { fclose(f); return total; }

    char codigoIngresado[64];
    printf("Ingrese el código del cupón: ");
    scanf("%63s", codigoIngresado);

    FILE *temp = fopen("cupones_tmp.txt", "w");
    if (!temp) { printf("Error interno.\n"); fclose(f); return total; }

    char codigo[64];
    int descuento;
    int encontrado = 0;
    float totalFinal = total;

    while (fscanf(f, "%63s %d", codigo, &descuento) == 2) {
        if (!encontrado && strcmp(codigo, codigoIngresado) == 0) {
            encontrado = 1;
            float rebaja = total * (descuento / 100.0f);
            totalFinal = total - rebaja;
            printf("✔ Cupón válido (%d%% de descuento)\n", descuento);
            printf("Descuento aplicado: -$%.2f\n", rebaja);
            printf("Total final: $%.2f\n", totalFinal);
            continue;
        }
        fprintf(temp, "%s %d\n", codigo, descuento);
    }

    fclose(f);
    fclose(temp);

    remove("cupones.txt");
    rename("cupones_tmp.txt", "cupones.txt");

    if (!encontrado) {
        printf("Cupón no encontrado o inválido.\n");
        return total;
    }

    return totalFinal;
}

// ================== PLANES ==================

void mostrarPlanes()
{
    printf("\n========== PLANES WHISKERPETS ==========\n");

    printf("\n[1] PLAN BASICO\n");
    printf("---------------------------------------\n");
    printf("- Acceso a compra de productos\n");
    printf("- Soporte basico por correo\n");
    printf("- Sin descuentos permanentes\n");
    printf("- No incluye cupon mensual\n");

    printf("\n[2] PLAN REGULAR\n");
    printf("---------------------------------------\n");
    printf("- Acceso a compra de productos\n");
    printf("- Soporte prioritario\n");
    printf("- 5%% de descuento permanente\n");
    printf("- 1 cupon mensual del 10%%\n");

    printf("\n[3] PLAN PREMIUM\n");
    printf("---------------------------------------\n");
    printf("- Acceso completo VIP\n");
    printf("- Soporte 24/7\n");
    printf("- 10%% de descuento permanente\n");
    printf("- 2 cupones mensuales del 20%%\n");
    printf("- Envio gratis\n");
    printf("- Acceso a ofertas exclusivas\n");

    printf("\n========================================\n");
}

void elegirPlan(char plan[])
{
    int opcionPlan;

    printf("\nSeleccione un plan para el usuario:\n");
    printf("1. BASICO\n");
    printf("2. REGULAR\n");
    printf("3. PREMIUM\n");
    printf("Opción: ");
    if (scanf("%d", &opcionPlan) != 1) { limpiarBuffer(); opcionPlan = 1; }

    switch (opcionPlan) {
        case 2:
            strcpy(plan, "REGULAR");
            break;
        case 3:
            strcpy(plan, "PREMIUM");
            break;
        case 1:
        default:
            strcpy(plan, "BASICO");
            break;
    }
}

float aplicarDescuentoPlan(float total, char plan[])
{
    if (strcmp(plan, "REGULAR") == 0)
        return total * 0.95f;    // 5%
        
    if (strcmp(plan, "PREMIUM") == 0)
        return total * 0.90f;    // 10%

    return total; // BASICO
}

void generarCuponPorPlan(char plan[])
{
    FILE *f = fopen("cupones.txt", "a");

    if (!f) return;

    if (strcmp(plan, "REGULAR") == 0)
        fprintf(f, "REGU10 10\n");

    if (strcmp(plan, "PREMIUM") == 0)
    {
        fprintf(f, "PREM20A 20\n");
        fprintf(f, "PREM20B 20\n");
    }

    fclose(f);
}

