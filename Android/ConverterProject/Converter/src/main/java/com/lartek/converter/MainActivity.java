package com.lartek.converter;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.support.v4.app.NavUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Toast;

public class MainActivity extends Activity {
    private EditText text;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        text = (EditText) findViewById(R.id.textField);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    public void calculate(View view) {
        switch (view.getId()) {
            case R.id.button:
                RadioButton celsiusButton = (RadioButton) findViewById(R.id.radio0);
                RadioButton kelvinButton = (RadioButton) findViewById(R.id.radio1);

                if (text.getText().length() == 0) {
                    Toast.makeText(this, "Please enter a valid number", Toast.LENGTH_LONG).show();
                    return;
                }

                double inputValue = Double.parseDouble(text.getText().toString());

                if(celsiusButton.isChecked()) {
                    text.setText(String.valueOf(kelvinToCelsius(inputValue)));
                    celsiusButton.setChecked(false);
                    kelvinButton.setChecked(true);
                }
                else {
                    text.setText(String.valueOf(celsiusToKelvin(inputValue)));
                    kelvinButton.setChecked(false);
                    celsiusButton.setChecked(true);
                }
                break;
        }
    }

    public void gotToSensorScreen (View view) {
        Intent intent = new Intent(this, sensor.class);
        startActivity(intent);
    }

    private double kelvinToCelsius(double kelvin) {
        return (kelvin - 273.15);
    }

    private double celsiusToKelvin(double celsius) {
        return (celsius + 273.15);
    }
}
