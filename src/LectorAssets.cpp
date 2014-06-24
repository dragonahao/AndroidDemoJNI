//
//  LectorAssets.cpp
//
//  Created by Marcos Ortega Morales on 21/06/2014.
//

#include "LectorAssets.h"
#include <stdlib.h> //para malloc y free
#include <android/log.h>

#define PRINTF_INFO(STR_FMT, ...)		__android_log_print(ANDROID_LOG_INFO, "DemoJNI", STR_FMT, ##__VA_ARGS__) //((void)0)
#define PRINTF_ERROR(STR_FMT, ...)		__android_log_print(ANDROID_LOG_ERROR, "DemoJNI", "ERROR, "STR_FMT, ##__VA_ARGS__)
#define PRINTF_WARNING(STR_FMT, ...)	__android_log_print(ANDROID_LOG_WARN, "DemoJNI", "WARNING, "STR_FMT, ##__VA_ARGS__)

#define LECTOR_ASSETS_TAM_BUFFER	1024

AAssetManager* LectorAssets::_apkAssetsMgr = NULL;
char* LectorAssets::_tmpContenido = NULL;
int LectorAssets::_tmpContenidoUso = 0;
int LectorAssets::_tmpContenidoTamano = 0;

bool LectorAssets::inicializar(AAssetManager* apkAssetsMgr){
	_apkAssetsMgr 	= apkAssetsMgr;
	//
	_tmpContenidoTamano = 1;
	_tmpContenidoUso 	= 0;
	_tmpContenido		= (char*) malloc(sizeof(char) * _tmpContenidoTamano);
	_tmpContenido[0]	= '\0';
	PRINTF_INFO("Lector de Assets inicializado.\n");
	return true;
}

const char* LectorAssets::dameContenidoAssetEnPaquete(const char* rutaVirtualArchivo){
	//AAssetManager_open solo funciona para archivos que fueron incluidos sin comprimir en el APK.
	//Por defecto, las herramientas de Android deciden cuales assets deben comprimirse y cuales no, a partir de la extensi—n del archivo.
	//Por ejemplo: los txt, xml, html se comprimen; los mp3, zip, png no se comprimen.
	//
	LectorAssets::contenidoTmpVaciar();
	AAsset* archivo		= AAssetManager_open(_apkAssetsMgr, rutaVirtualArchivo, AASSET_MODE_RANDOM);
	if(archivo == NULL){
		PRINTF_ERROR("No se pudo abrir el archivo asset '%s'.\n", rutaVirtualArchivo);
	} else {
		PRINTF_INFO("Archivo asset abierto '%s'.\n", rutaVirtualArchivo);
		//Leer el contenido
		char buffer[LECTOR_ASSETS_TAM_BUFFER];
		int bytesLeidos;
		do {
			bytesLeidos = AAsset_read(archivo, buffer, LECTOR_ASSETS_TAM_BUFFER);
			if(bytesLeidos > 0){
				LectorAssets::contenidoTmpConcatenar(buffer, bytesLeidos);
			}
		} while(bytesLeidos != 0);
		//Cerrar archivo
		AAsset_close(archivo);
		PRINTF_INFO("Archivo asset cerrado.\n");
	}
	return _tmpContenido;
}

void LectorAssets::finalizar(){
	if(_tmpContenido != NULL){
		free(_tmpContenido);
	}
	_tmpContenido 		= NULL;
	_tmpContenidoTamano = 0;
	_tmpContenidoUso 	= 0;
	PRINTF_INFO("Lector de Assets finalizado.\n");
}

//

void LectorAssets::contenidoTmpVaciar(){
	_tmpContenidoUso = 0;
}

void LectorAssets::contenidoTmpConcatenar(const char* str, const int cantBytes){
	//Redimensionar el buffer (si es necesario)
	if((_tmpContenidoUso + cantBytes + 1) > _tmpContenidoTamano){ //+1 para el '\0'
		_tmpContenidoTamano = (_tmpContenidoUso + cantBytes + 1);
		char* nuevoBuffer = (char*) malloc(sizeof(char) * _tmpContenidoTamano);
		if(_tmpContenido != NULL){
			int i; for(i = 0; i < _tmpContenidoUso; i++) nuevoBuffer[i] = _tmpContenido[i];
		}
		free(_tmpContenido);
		_tmpContenido = nuevoBuffer;
	}
	//Concatenar el contenido
	int i;
	for(i = 0; i < cantBytes; i++){
		_tmpContenido[_tmpContenidoUso++] = str[i];
	}
	//Agregar un caracter de fin de cadena
	_tmpContenido[_tmpContenidoUso] = '\0';
}




