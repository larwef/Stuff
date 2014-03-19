package com.lartek.wagecalculator20;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.Toast;

import java.util.Calendar;
import java.util.List;

public class Delete extends Activity {

    private int fromYear;
    private int fromMonth;
    private int fromDay;

    private int toYear;
    private int toMonth;
    private int toDay;

    boolean deleteAll;

    private Button pickFromButton;
    private Button pickToButton;
    private EditText fromDateField;
    private EditText toDateField;

    private DatabaseHandler db;

    static final int FROM_DATE_DIALOG_ID = 3;
    static final int TO_DATE_DIALOG_ID = 4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.delete_layout);

        deleteAll = false;

        fromYear = -1;

        toYear = -1;

        final Calendar cal = Calendar.getInstance();
        fromYear = cal.get(Calendar.YEAR);
        fromMonth = cal.get(Calendar.MONTH);
        fromDay = cal.get(Calendar.DAY_OF_MONTH);

        toYear = cal.get(Calendar.YEAR);
        toMonth = cal.get(Calendar.MONTH);
        toDay = cal.get(Calendar.DAY_OF_MONTH);

        pickFromButton = (Button) findViewById(R.id.delFromPickBtn);
        pickToButton = (Button) findViewById(R.id.delToPickBtn);
        fromDateField = (EditText) findViewById(R.id.delFromInput);
        toDateField = (EditText) findViewById(R.id.delToInput);

        fromDateField.setFocusable(false);
        toDateField.setFocusable(false);

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
        getMenuInflater().inflate(R.menu.delete, menu);
        return true;
    }

    DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {
            switch (which){
                case DialogInterface.BUTTON_POSITIVE:

                    if(deleteAll == true) {
                        deleteAllEntries();
                        deleteAll = false;
                    }
                    else {
                        deleteSelectedEntries();
                    }
                    break;

                case DialogInterface.BUTTON_NEGATIVE:
                    //Do nothing
                    break;
            }
        }
    };

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

            fromDateField.setText(new StringBuilder()
                    .append(fromDay).append("/")
                    .append(fromMonth + 1).append("/")
                    .append(fromYear));

            toYear = thisYear;
            toMonth = monthOfYear;
            toDay = dayOfMonth;

            toDateField.setText(new StringBuilder()
                    .append(toDay).append("/")
                    .append(toMonth + 1).append("/")
                    .append(toYear));
        }
    };

    private DatePickerDialog.OnDateSetListener
            toListener = new DatePickerDialog.OnDateSetListener() {
        public void onDateSet(DatePicker view, int thisYear, int monthOfYear, int dayOfMonth) {
            final Calendar cal = Calendar.getInstance();
            toYear = thisYear;
            toMonth = monthOfYear;
            toDay = dayOfMonth;

            toDateField.setText(new StringBuilder()
                    .append(toDay).append("/")
                    .append(toMonth + 1).append("/")
                    .append(toYear));
        }
    };

    public void deleteAll(View view) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("Are you sure?").setPositiveButton("Yes", dialogClickListener)
                .setNegativeButton("No", dialogClickListener).show();

        deleteAll = true;

        return;
    }

    public void deleteAllEntries() {
        db = new DatabaseHandler(this);
        List<WorkDay> workdays = db.getAllWorkDays();
        for (WorkDay cn : workdays) {
            db.deleteWorkDay(cn);
        }
        Toast.makeText(this, "All entries have been deleted", Toast.LENGTH_LONG).show();

        return;
    }

    public void deleteSelection(View view) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("Are you sure?").setPositiveButton("Yes", dialogClickListener)
                .setNegativeButton("No", dialogClickListener).show();
    }

    private void deleteSelectedEntries() {
        if(fromYear == -1 || toYear == -1) {
            Toast.makeText(this, "Provide from and to date", Toast.LENGTH_LONG).show();
            return;
        }

        int fromComp;
        int toComp;

        WorkDay from = new WorkDay(fromDay, fromMonth, fromYear, -1, -1, -1);
        WorkDay to = new WorkDay(toDay, toMonth, toYear, -1, -1, -1);

        db = new DatabaseHandler(this);
        List<WorkDay> workdays = db.getAllWorkDays();
        for(WorkDay cn : workdays) {
            fromComp = cn.compareTo(from);
            toComp = cn.compareTo(to);

            if((fromComp * toComp) <= 0 && fromComp >= 0 && toComp <= 0) {
                db.deleteWorkDay(cn);
            }
        }
        Toast.makeText(this, "Selection has been deleted", Toast.LENGTH_LONG).show();

        return;
    }
}
