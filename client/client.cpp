#include "client.h"

Client::Client(Socket &&socket) : skt(std::move(socket)), protocolo(std::ref(skt)), was_closed(false) {}

Client::~Client() {}

/*
 * Se encarga de indicarle al protocolo que debe recibir la cantidad de veces indicada por consola
 * en el comando "Read n" para luego imprimirlo por pantalla.
 */
void Client::receiveNTimes(std::string data, size_t pos)
{
    // int n = std::stoi(data.substr(pos + 1));

    // for (int i = 0; i < n; i++)
    // {
    //     Dto *dto = protocolo.receive(was_closed);
    //     // std::cout << dto->message() << std::endl;
    //     delete dto;
    // }
}

/*
 * Cierra la conversacion con el servidor.
 */
void Client::closeEverything()
{
    skt.shutdown(2);
    skt.close();
    was_closed = true;
}

/*
 * Recibe por entrada estandar una serie de caracteres y de interpretarlos segun corresponda
 * para luego enviarselo al servidor
 */
void Client::encode(std::string data)
{
    size_t pos = data.find(' ');
    std::string first_word = data.substr(0, pos);

    if (first_word == "move")
        protocolo.handle_move(was_closed);
    else if (first_word == "jump")
        protocolo.handle_jump(static_cast<uint8_t>(std::stoi(data.substr(pos + 1))), was_closed);
    else if (first_word == "dir")
        protocolo.handle_dir(static_cast<uint8_t>(std::stoi(data.substr(pos + 1))), was_closed);
    else if (first_word == EXIT)
        closeEverything();
    else
        std::cerr << "Instruccion no identificada, ingresela nuevamente." << std::endl;
    return;
}

void Client::addLineToMap(Dto *dto, int fila)
{

    int col = 0;
    int tope = (dto->return_line()).size();
    std::string linea(dto->return_line());
    for (int i = 0; i < tope; i++)
    {
        matriz[fila][i] = linea[i];
        col++;
    }
    columnas = col;
    filas = fila;
}

void Client::chargeMap()
{
    matriz.resize(5, std::vector<char>(9));
    Dto *dto;
    bool is_notcomplete = true;
    int fila = 0;
    while (is_notcomplete)
    {
        dto = protocolo.receive(was_closed);
        if (dto->return_line() == "fin")
            is_notcomplete = false;
        else
            addLineToMap(dto, fila);

        fila++;
    }
}

void Client::imprimirMapa()
{
    for (int i = 0; i <= filas; i++)
    {
        for (int j = 0; j < columnas; j++)
            std::cout << matriz[i][j];
        std::cout << "\n";
    }
}

void Client::receivePosition()
{
    if (not(x == 0 && y == 0))
        matriz[y][x] = ' ';

    Dto *pos = protocolo.recibir_posicion(was_closed);
    x = pos->x_pos();
    y = pos->y_pos();
    matriz[y][x] = 'G';
    imprimirMapa();
}

void Client::start()
{

    std::string data;

    chargeMap();
    receivePosition();

    while (not was_closed)
    {
        data.clear();

        std::getline(std::cin, data);

        if (data.empty())
            break;

        encode(data);

        if (was_closed)
            break;

        // protocolo.recibir_posicion(was_closed);
        receivePosition();

        if (was_closed)
            break;
    }
    return;
}
