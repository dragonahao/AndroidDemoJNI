package demo.marcos.ortega.jni;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {

	private AppNativo _interfazNativa = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		//Inicializar
		_interfazNativa = new AppNativo(); 
		_interfazNativa.inicializar(getResources().getAssets());
		//Cargar contenido de Asset desde JNI
		String contenidoArchivo = _interfazNativa.dameContenidoAsset("archivoTexto.png"); //el archivo es de texto, pero le colocamos la extension "png" para evitar que Android lo comprima dentro del APK.
		//Imprimir contenido (en consola y pantalla)
		System.out.println("Contenido de archivo: " + contenidoArchivo);
		TextView t = (TextView) findViewById(R.id.txt_hello_world);
		t.setText("Contenido cargardo de JNI: " + contenidoArchivo);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}
