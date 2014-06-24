package demo.marcos.ortega.jni;

public class AppNativo {

	static {
		System.loadLibrary("lectorassets");
	}
	
	public boolean inicializar(Object assetManager){
		return nativeInicializar(assetManager);
	}
	
	public String dameContenidoAsset(String rutaVirtual){ //la ruta debe iniciar con "apk:..."
		return nativeDameContenidoAsset(rutaVirtual);
	}
	
	public void finalizar(){
		nativeFinalizar();
	}
	
	private native boolean	nativeInicializar(Object assetManager);
	private native String	nativeDameContenidoAsset(String rutaVirtual); //la ruta debe iniciar con "apk:..."
	private native void		nativeFinalizar();
	
}
