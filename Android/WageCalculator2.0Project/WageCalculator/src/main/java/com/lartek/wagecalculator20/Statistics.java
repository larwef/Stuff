package com.lartek.wagecalculator20;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Statistics extends Activity {

    private int statMonth;
    private int statYear;

    private EditText statDateOutput;
    private EditText statHoursOutput;
    private EditText statResultOutput;
    private RadioButton monthYear;
    private RadioButton justYear;
    private Button plusButton;
    private Button minusButton;
    private TextView repDate;
    private TextView repHours;
    private TextView repRate;
    private TextView repResult;

    private List<WorkDay> workdays;

    private DatabaseHandler db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.statistics_layout);

        statDateOutput = (EditText) findViewById(R.id.statDate);
        statHoursOutput = (EditText) findViewById(R.id.statHoursField);
        statResultOutput = (EditText) findViewById(R.id.statResultField);
        monthYear = (RadioButton) findViewById(R.id.radio0);
        justYear = (RadioButton) findViewById(R.id.radio1);
        plusButton = (Button) findViewById(R.id.plusBtn);
        minusButton = (Button) findViewById(R.id.minusBtn);
        repDate = (TextView) findViewById(R.id.reportDate);
        repHours = (TextView) findViewById(R.id.reportHours);
        repRate = (TextView) findViewById(R.id.reportRate);
        repResult = (TextView) findViewById(R.id.reportResult);

        statHoursOutput.setFocusable(false);
        statResultOutput.setFocusable(false);
        statDateOutput.setFocusable(false);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            // Show the Up button in the action bar.
            getActionBar().setDisplayHomeAsUpEnabled(true);
        }

        final Spinner spinner = (Spinner) findViewById(R.id.monthSpinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.monthArray, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        monthYear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                displayStat();
            }
        });

        justYear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                displayStat();
            }
        });

        statSetCurrentDate();

        displayStat();

        spinner.setSelection(statMonth);

        statDateOutput.setText(String.valueOf(statYear));

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                statMonth = spinner.getSelectedItemPosition();
                displayStat();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                displayStat();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.statistics, menu);

        return true;
    }

    public void statSetCurrentDate() {
        final Calendar cal = Calendar.getInstance();
        statYear = cal.get(Calendar.YEAR);
        statMonth = cal.get(Calendar.MONTH);

        return;
    }

    private void displayStat(){
        repDate.setText("");
        repHours.setText("");
        repRate.setText("");
        repResult.setText("");

        List<WorkDay> displayList;

        if (monthYear.isChecked()) {
            displayList = getListByMonth();
        }
        else {
            displayList = getListByYear();
        }

        double thisHours = 0;
        double thisResult = 0;

        for (WorkDay cn : displayList) {
            thisHours += cn.hours;
            thisResult += cn.result;
            makeReportLine(cn);
        }
        statHoursOutput.setText(String.valueOf(thisHours));
        statResultOutput.setText(String.valueOf(thisResult));

        return;
    }

    public void plus(View view) {
        statYear += 1;
        statDateOutput.setText(String.valueOf(statYear));
        displayStat();
        return;
    }

    public void minus(View view) {
        statYear -= 1;
        statDateOutput.setText(String.valueOf(statYear));
        displayStat();
        return;
    }

    public void makeReportLine(WorkDay wd) {
        repDate.append(String.valueOf(wd.day) + "/" + String.valueOf(wd.month + 1) + "/" + String.valueOf(wd.year) + "\n");
        repHours.append(String.valueOf(wd.hours) + "\n");
        repRate.append(String.valueOf(wd.rate) + "\n");
        repResult.append(String.valueOf(wd.result) + "\n");
    }

    public List<WorkDay> getListByMonth() {
        List<WorkDay> byMonth = new LinkedList<WorkDay>();
        db = new DatabaseHandler(this);
        List<WorkDay> workdays = db.getAllWorkDays();
        for (WorkDay cn : workdays) {
            if (cn.month == statMonth && cn.year == statYear) {
                byMonth.add(cn);
            }
        }
        Collections.sort(byMonth);
        return byMonth;
    }
    public List<WorkDay> getListByYear() {
        List<WorkDay> byYear = new LinkedList<WorkDay>();
        db = new DatabaseHandler(this);
        List<WorkDay> workdays = db.getAllWorkDays();
        for (WorkDay cn : workdays) {
            if (cn.year == statYear) {
                byYear.add(cn);
            }
        }
        Collections.sort(byYear);

        return byYear;
    }

    public void gotToDeleteScreen(View view) {
        Intent intent = new Intent(this, Delete.class);
        startActivity(intent);

        return;
    }

    public void gotToFromTo (View view) {
        Intent intent = new Intent(this, FromTo.class);
        startActivity(intent);

        return;
    }
}
