package com.lartek.wagecalculator20;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Calendar;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class FromTo extends Activity {

    private int fromYear;
    private int fromMonth;
    private int fromDay;

    private int toYear;
    private int toMonth;
    private int toDay;

    private EditText fromToFromInput;
    private EditText fromToToInput;
    private EditText fromToHoursOutput;
    private EditText fromToResultOutput;
    private TextView fromToDate;
    private TextView fromToHours;
    private TextView fromToRate;
    private TextView fromToResult;
    private Button pickFromButton;
    private Button pickToButton;

    private boolean fromIsSet;
    private boolean toIsSet;

    static final int FROM_DATE_DIALOG_ID = 1;
    static final int TO_DATE_DIALOG_ID = 2;

    private DatabaseHandler db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fromto_layout);

        fromIsSet = false;
        toIsSet = false;

        final Calendar cal = Calendar.getInstance();
        fromYear = cal.get(Calendar.YEAR);
        fromMonth = cal.get(Calendar.MONTH);
        fromDay = cal.get(Calendar.DAY_OF_MONTH);

        toYear = cal.get(Calendar.YEAR);
        toMonth = cal.get(Calendar.MONTH);
        toDay = cal.get(Calendar.DAY_OF_MONTH);

        fromToFromInput = (EditText) findViewById(R.id.fromInput);
        fromToToInput = (EditText) findViewById(R.id.toInput);
        fromToHoursOutput = (EditText) findViewById(R.id.fromToHoursField);
        fromToResultOutput = (EditText) findViewById(R.id.fromToResultField);
        fromToDate = (TextView) findViewById(R.id.fromToReportDate);
        fromToHours = (TextView) findViewById(R.id.fromToReportHours);
        fromToRate = (TextView) findViewById(R.id.fromToReportRate);
        fromToResult= (TextView) findViewById(R.id.fromToReportResult);
        pickFromButton = (Button) findViewById(R.id.fromPickBtn);
        pickToButton = (Button) findViewById(R.id.toPickBtn);

        fromToHoursOutput.setFocusable(false);
        fromToResultOutput.setFocusable(false);
        fromToFromInput.setFocusable(false);
        fromToToInput.setFocusable(false);

        pickFromButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showDialog(FROM_DATE_DIALOG_ID);
            }
        });

        pickToButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showDialog(TO_DATE_DIALOG_ID);
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.from_to, menu);
        return true;
    }

    @Override
    protected Dialog onCreateDialog(int id) {
        switch (id) {
            case FROM_DATE_DIALOG_ID:
                return new DatePickerDialog(this, fromListener, fromYear, fromMonth, fromDay);
            case TO_DATE_DIALOG_ID:
                return new DatePickerDialog(this, toListener, toYear, toMonth, toDay);

        }
        return null;
    }

    private DatePickerDialog.OnDateSetListener
            fromListener = new DatePickerDialog.OnDateSetListener() {
        public void onDateSet(DatePicker view, int thisYear, int monthOfYear, int dayOfMonth) {
            final Calendar cal = Calendar.getInstance();
            fromYear = thisYear;
            fromMonth = monthOfYear;
            fromDay = dayOfMonth;

            fromToFromInput.setText(new StringBuilder()
                    .append(fromDay).append("/")
                    .append(fromMonth + 1).append("/")
                    .append(fromYear));

            fromIsSet = true;

            if (fromIsSet == true && toIsSet == true) {
                fromToDisplayStat();
            }
        }
    };

    private DatePickerDialog.OnDateSetListener
            toListener = new DatePickerDialog.OnDateSetListener() {
        public void onDateSet(DatePicker view, int thisYear, int monthOfYear, int dayOfMonth) {
            final Calendar cal = Calendar.getInstance();
            toYear = thisYear;
            toMonth = monthOfYear;
            toDay = dayOfMonth;

            fromToToInput.setText(new StringBuilder()
                    .append(toDay).append("/")
                    .append(toMonth + 1).append("/")
                    .append(toYear));

            toIsSet = true;

            if (fromIsSet == true && toIsSet == true) {
                fromToDisplayStat();
            }
        }
    };

    private List<WorkDay> getList() {
        List<WorkDay> theList = new LinkedList<WorkDay>();

        WorkDay from = new WorkDay(fromDay, fromMonth, fromYear, -1, -1, -1);
        WorkDay to = new WorkDay(toDay, toMonth, toYear, -1, -1, -1);

        int fromComp;
        int toComp;

        db = new DatabaseHandler(this);
        List<WorkDay> workdays = db.getAllWorkDays();
        for(WorkDay cn : workdays) {
            fromComp = cn.compareTo(from);
            toComp = cn.compareTo(to);

            if((fromComp * toComp) <= 0 && fromComp >= 0 && toComp <= 0) {
                theList.add(cn);
            }
        }

        Collections.sort(theList);
        return theList;
    }

    public void fromToDisplayStat() {
        fromToDate.setText("");
        fromToHours.setText("");
        fromToRate.setText("");
        fromToResult.setText("");


        List<WorkDay> displayList = getList();

        double thisHours = 0;
        double thisResult = 0;

        for (WorkDay cn : displayList) {
            thisHours += cn.hours;
            thisResult += cn.result;
            fromToMakeReportLine(cn);
        }
        fromToHoursOutput.setText(String.valueOf(thisHours));
        fromToResultOutput.setText(String.valueOf(thisResult));

        return;
    }

    public void fromToMakeReportLine(WorkDay wd) {
        fromToDate.append(String.valueOf(wd.day) + "/" + String.valueOf(wd.month + 1) + "/" + String.valueOf(wd.year) + "\n");
        fromToHours.append(String.valueOf(wd.hours) + "\n");
        fromToRate.append(String.valueOf(wd.rate) + "\n");
        fromToResult.append(String.valueOf(wd.result) + "\n");

        return;
    }

}
