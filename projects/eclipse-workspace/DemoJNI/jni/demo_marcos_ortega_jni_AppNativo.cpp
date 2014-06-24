
#include "demo_marcos_ortega_jni_AppNativo.h"
#include "LectorAssets.h"

JNIEXPORT jboolean JNICALL Java_demo_marcos_ortega_jni_AppNativo_nativeInicializar(JNIEnv* entorno, jobject instancia, jobject assetsManager){
	LectorAssets::inicializar(AAssetManager_fromJava(entorno, assetsManager));
	return JNI_TRUE;
}

JNIEXPORT jstring JNICALL Java_demo_marcos_ortega_jni_AppNativo_nativeDameContenidoAsset(JNIEnv* entorno, jobject instancia, jstring rutaVirtualAsset){
	const char* strRutaNativa 		= entorno->GetStringUTFChars(rutaVirtualAsset, 0);
	//Leer contenido de archivo
	const char* contenidoArchivo	= LectorAssets::dameContenidoAssetEnPaquete(strRutaNativa);
	jstring jStrConrtenido 			= entorno->NewStringUTF(contenidoArchivo);
	//
	entorno->ReleaseStringUTFChars(rutaVirtualAsset, strRutaNativa);
	return jStrConrtenido;
}

JNIEXPORT void JNICALL Java_demo_marcos_ortega_jni_AppNativo_nativeFinalizar(JNIEnv* entorno, jobject instancia){
	LectorAssets::finalizar();
}
