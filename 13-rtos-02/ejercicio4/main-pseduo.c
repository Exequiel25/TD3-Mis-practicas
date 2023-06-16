/*

En la tarea ImprimeHora mostrada en la página 95 del libro Sistemas Empotrados en Tiempo Real, ¿se podría solucionar el arbitraje del acceso al puerto serie cortando las interrupciones mientras se llama a SeriePuts()? En caso afirmativo, ¿existe alguna ventaja en el uso de semáforos?

BOARD: EDU CIAA

Para este caso no es útil SeriePuts() para el arbitraje cortando las interrupciones.
La ventaja de usar semáforos es que se pueden usar en zonas críticas para evitar concurrencias.

*/

void ImprimeHora(void)
{
    HORA copia_hora;
    char cadena[10];
    while (1)
    {
        /* Se Bloquea hasta que llegue la interrupción
    de tiempo */
        Disable(); /* Se copia la variable compartida
       con la interrupción */
        copia_hora = hora_act;
        Enable();
        sprintf(cadena, " %02d: %02d: %02d\n", copia_hora.hora,
                copia_hora.min, copia_hora.seg);
        xSemaphoreTake();
        SeriePuts(cadena);
        xSemaphoreGive();
    }
}

void EnviaEntradas(void)
{
    char cadena[100]; /* Guarda el mensaje a transmitir */
    uint8 entradas;
    static uint8 entradas_ant = 0;
    while (1)
    {
        entradas = LeeEntradas();
        if (entradas_ant != entradas)
        { /* Sólo imprime si
cambian las entradas */
            sprintf(cadena, " Entradas : %x\n", entradas);
            SemaphoreTake();
            SeriePuts(cadena);
            SemaphoreGive();
            entradas_ant = entradas;
        }
    }
