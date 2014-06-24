//
//  LectorAssets.h
//
//  Created by Marcos Ortega Morales on 21/06/2014.
//

#ifndef LECTORASSETS_H_INCLUIDO
#define LECTORASSETS_H_INCLUIDO

#include <android/asset_manager_jni.h>

class LectorAssets {
	public:
		static bool 		inicializar(AAssetManager* apkAssetsMgr);
		static const char*	dameContenidoAssetEnPaquete(const char* rutaVirtualArchivo);
		static void 		finalizar();
	private:
		static AAssetManager* _apkAssetsMgr;
		static char* _tmpContenido;
		static int _tmpContenidoUso;
		static int _tmpContenidoTamano;
		//
		static void contenidoTmpVaciar();
		static void contenidoTmpConcatenar(const char* str, const int cantBytes);
};

#endif
