package com.lartek.wagecalculator20;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.content.Intent;
import android.os.Bundle;
import android.app.Activity;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Calendar;

public class MainActivity extends Activity {

    private int year;
    private int month;
    private int day;
    private double hours;
    private double rate;
    private double result;

    private EditText dateOutput;
    private Button datePickBtn;
    private EditText hoursInput;
    private EditText rateInput;
    private EditText resultOutput;
    static final int DATE_DIALOG_ID = 0;

    private DatabaseHandler db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dateOutput = (EditText) findViewById(R.id.dateField);
        datePickBtn = (Button) findViewById(R.id.dateBtn);
        hoursInput = (EditText) findViewById(R.id.hoursField);
        rateInput = (EditText) findViewById(R.id.rateField);
        resultOutput = (EditText) findViewById(R.id.resultField);

        resultOutput.setFocusable(false);
        dateOutput.setFocusable(false);

        datePickBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showDialog(DATE_DIALOG_ID);
            }
        });

        hoursInput.addTextChangedListener(new TextWatcher() {

            public void afterTextChanged(Editable s) {
                updateResult();
            }

            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {
            }

            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {
            }
        });

        rateInput.addTextChangedListener(new TextWatcher() {

            public void afterTextChanged(Editable s) {
                updateResult();
            }

            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {
            }

            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {
            }
        });

        setCurrentDate();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    protected Dialog onCreateDialog(int id) {
        switch (id) {
            case DATE_DIALOG_ID:
                return new DatePickerDialog(this, DateSetListener, year, month, day);
        }
        return null;
    }

    private DatePickerDialog.OnDateSetListener
    DateSetListener = new DatePickerDialog.OnDateSetListener() {
        public void onDateSet(DatePicker view, int thisYear, int monthOfYear, int dayOfMonth) {
            final Calendar cal = Calendar.getInstance();
            year = thisYear;
            month = monthOfYear;
            day = dayOfMonth;
            setDate();
        }
    };

    public void setCurrentDate() {
        final Calendar cal = Calendar.getInstance();
        year = cal.get(Calendar.YEAR);
        month = cal.get(Calendar.MONTH);
        day = cal.get(Calendar.DAY_OF_MONTH);

        dateOutput.setText(new StringBuilder()
                .append(day).append("/")
                .append(month + 1).append("/")
                .append(year));
        return;
    }

    public void setDate() {
        dateOutput.setText(new StringBuilder()
                .append(day).append("/")
                .append(month + 1).append("/")
                .append(year));
        return;
    }

    private void updateResult() {
        if(hoursInput.getText().length() == 0 || rateInput.getText().length() == 0){
            resultOutput.setText(" ");
        }
        else {
            hours = Double.parseDouble(hoursInput.getText().toString());
            rate = Double.parseDouble(rateInput.getText().toString());

            result = (rate * hours);

            resultOutput.setText(String.valueOf(result));
        }
        return;
    }

    public void addToDataBase (View view) {
        if(resultOutput.getText().length() != 0 && hoursInput.getText().length() != 0 && rateInput.getText().length() != 0) {
            db = new DatabaseHandler(this);
            db.addWorkDay(new WorkDay(day, month, year, hours, rate, result));
            Toast.makeText(this, "Added successfully", Toast.LENGTH_SHORT).show();
        }
        else {
            Toast.makeText(this, "Provide valid input", Toast.LENGTH_SHORT).show();
        }
        return;
    }

    public void gotToStatisticsScreen (View view) {
        Intent intent = new Intent(this, Statistics.class);
        startActivity(intent);
        return;
    }
}
