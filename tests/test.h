#pragma once
#include <bits/stdc++.h>

using TipoVariable = std::variant<int, long, std::string, std::vector<int>>;

// --- INICIO DEL INTERNO: NO TOCAR PARA NADA ESTA PARTE --- //
template<typename T>
T extraer(const TipoVariable& variable){
    return std::get<T>(variable);
}

template<typename Retorno, typename... Args, size_t... Is>
Retorno invocar_impl(Retorno (*func)(Args...), const std::vector<TipoVariable> & variables, std::index_sequence<Is...>){
    return func(extraer<Args>(variables[Is])...);
}

template<typename Retorno, typename... Args>
Retorno llamar_funcion(Retorno(*func)(Args...), const std::vector<TipoVariable>& variables){
    if (variables.size() < sizeof...(Args)) {
        throw std::runtime_error("Error: El vector no tiene suficientes parametros para la funcion.");

    }
    return invocar_impl<Retorno, Args...>(func, variables, std::make_index_sequence<sizeof...(Args)>{});

}

// --- FIN DEL INTERNO--- //



std::string limpiar_string(const std::string & cadena_a_limpiar){
    size_t start = cadena_a_limpiar.find_first_not_of(" \t\"\'");
    size_t end = cadena_a_limpiar.find_last_not_of(" \t\"\';");

    if (start == std::string::npos) return "";

    return cadena_a_limpiar.substr(start, end - start + 1);
}

std::vector<TipoVariable> obtener_parametros_por_caso(const std::filesystem::path & ruta_archivo){
    std::vector<TipoVariable> lista_parametros;

    std::ifstream archivo(ruta_archivo);

    if (!archivo.is_open()){
        std::cerr << "Error al abrir el archivo" << std::endl;
        return lista_parametros;
    }

    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string nombre, tipo_valor, valor_raw;

        std::getline(ss, nombre, ',');
        std::getline(ss, tipo_valor, ',');
        std::getline(ss, valor_raw, ',');

        nombre = limpiar_string(nombre);
        tipo_valor = limpiar_string(tipo_valor);
        std::string valor_limpio = limpiar_string(valor_raw);

        if (tipo_valor == "int"){
            try{
                lista_parametros.push_back(std::stoi(valor_limpio));
            }catch (const std::exception & e){
                std::cerr << "Error al convertir a entero " << valor_limpio << std::endl;
            }
        }else if (tipo_valor == "string"){
            lista_parametros.push_back(valor_limpio);
        }else if(tipo_valor == "long"){
            try{
                lista_parametros.push_back(std::stol(valor_limpio));
            }catch (const std::exception & e){
                std::cerr << "Error al convertir a long " << valor_limpio << std::endl;
            }
        }else if (tipo_valor == "vector<int>"){
            std::cout << "Tipo de variable en progreso" << std::endl; 
        }else{
            std::cerr << "Tipo de variable no existe en nuestra lista de variables disponibles" << std::endl;
        }
    }

    return lista_parametros;
}

std::vector<std::vector<TipoVariable>> obtener_parametros_y_respuesta(const std::string & ruta_carpeta){
    std::vector<std::vector<TipoVariable>> todos_los_casos;
    std::string extension = ".in";

    if (std::filesystem::exists(ruta_carpeta) && std::filesystem::is_directory(ruta_carpeta)) {
        for (const auto & entrada : std::filesystem::directory_iterator(ruta_carpeta)) {
            if (entrada.is_regular_file() && entrada.path().extension() == extension) {
                std::vector<TipoVariable> lista_parametros = obtener_parametros_por_caso(entrada.path());
                todos_los_casos.push_back(lista_parametros);
            }
        }
    }

    return todos_los_casos;
}

int obtener_numero_casos_pruebas(const std::string & ruta_carpeta){
    std::string extension = ".in";
    int contador = 0;

    if (std::filesystem::exists(ruta_carpeta) && std::filesystem::is_directory(ruta_carpeta)){
        for (const auto & entrada: std::filesystem::directory_iterator(ruta_carpeta)){
            if (entrada.is_regular_file() && entrada.path().extension() == extension){
                contador++;
            }
        }
        return contador;
    } else {
        return 0;
    }
}

inline bool verificar_si_existe_ruta(const std::string & ruta_direccion){
    std::ifstream f(ruta_direccion.c_str());
    return f.good();
}

template<typename Retorno, typename... Args>
std::pair<bool, std::string> test_function(std::string ruta_direccion, Retorno(*funcion)(Args...)){
    bool existe_ruta = verificar_si_existe_ruta(ruta_direccion);
    if (!existe_ruta){
        std::pair<bool, std::string> mensaje = {false, "Ruta determinada no existe"};
        return mensaje;
    }

    int numero_casos_pruebas = obtener_numero_casos_pruebas(ruta_direccion);
    
    std::vector<std::vector<TipoVariable>> parametros_y_respuestas = obtener_parametros_y_respuesta(ruta_direccion); // TODO

    for (int test = 0; test < (int) parametros_y_respuestas.size(); ++test){
        std::vector<TipoVariable> caso_prueba = parametros_y_respuestas[test];
        
        if (caso_prueba.empty()) continue;

        TipoVariable respuesta_esperada = caso_prueba.back();
        caso_prueba.pop_back();

        Retorno resultado_obtenido = llamar_funcion(funcion, caso_prueba);

        if (std::get<Retorno>(respuesta_esperada) == resultado_obtenido){
            continue;
        }else{
            return {false, "Fallo en un caso"};
        }
    }

    return {true, "Todos los test salieron correctamente :)"};
}