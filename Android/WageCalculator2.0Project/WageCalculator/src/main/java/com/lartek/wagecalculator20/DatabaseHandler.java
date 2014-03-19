package com.lartek.wagecalculator20;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;

public class DatabaseHandler extends SQLiteOpenHelper {
    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "workDaysManager";
    private static final String TABLE_WORKDAYS = "workDays";

    private static final String KEY_ID = "id";
    private static final String KEY_DAY = "day";
    private static final String KEY_MONTH = "month";
    private static final String KEY_YEAR = "year";
    private static final String KEY_HOURS = "hours";
    private static final String KEY_RATE = "rate";
    private static final String KEY_RESULT = "result";


    public DatabaseHandler(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }
    @Override
    public void onCreate (SQLiteDatabase db) {
        String CREATE_WORKDAYS_TABLE = "CREATE TABLE " + TABLE_WORKDAYS + "("
                + KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                + KEY_DAY + " INTEGER,"
                + KEY_MONTH + " INTEGER,"
                + KEY_YEAR + " INTEGER,"
                + KEY_HOURS + " INTEGER,"
                + KEY_RATE + " REAL,"
                + KEY_RESULT + " REAL" + ")";
        db.execSQL(CREATE_WORKDAYS_TABLE);
    }
    @Override
    public void onUpgrade (SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_WORKDAYS);
        onCreate(db);
    }

    void addWorkDay(WorkDay workday) {
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(KEY_DAY, workday.getDay());
        values.put(KEY_MONTH, workday.getMonth());
        values.put(KEY_YEAR, workday.getYear());
        values.put(KEY_HOURS, workday.getHours());
        values.put(KEY_RATE, workday.getRate());
        values.put(KEY_RESULT, workday.getResult());

        db.insert(TABLE_WORKDAYS, null, values);
        db.close();
    }

    public WorkDay getWorkday(int id) {
        SQLiteDatabase db = this.getReadableDatabase();
        assert db != null;
        Cursor cursor = db.query(TABLE_WORKDAYS, new String[] { KEY_ID,
                KEY_DAY, KEY_MONTH, KEY_YEAR, KEY_HOURS, KEY_RATE, KEY_RESULT },
                KEY_ID + " = ?",
                new String[] { String.valueOf(id) }, null, null, null, null);

        if(cursor != null){
            cursor.moveToFirst();
        }
        assert cursor != null;
        WorkDay workday;
        workday = new WorkDay(Integer.parseInt(cursor.getString(0)),
                Integer.parseInt(cursor.getString(1)),
                Integer.parseInt(cursor.getString(2)),
                Integer.parseInt(cursor.getString(3)),
                Double.parseDouble(cursor.getString(4)),
                Double.parseDouble(cursor.getString(5)),
                Double.parseDouble(cursor.getString(6)));

        return workday;
    }

    public List<WorkDay> getAllWorkDays() {
        List<WorkDay> workDayList = new ArrayList<WorkDay>();

        String selectQuery;
        selectQuery = ("SELECT  * FROM " + TABLE_WORKDAYS);

        SQLiteDatabase db = this.getWritableDatabase();
        assert db != null;
        Cursor cursor;
        cursor = db.rawQuery(selectQuery, null);

        if (cursor.moveToFirst()) {
            do {
                WorkDay workday = new WorkDay();
                workday.setId(Integer.parseInt(cursor.getString(0)));
                workday.setDay(Integer.parseInt(cursor.getString(1)));
                workday.setMonth(Integer.parseInt(cursor.getString(2)));
                workday.setYear(Integer.parseInt(cursor.getString(3)));
                workday.setHours(Double.parseDouble(cursor.getString(4)));
                workday.setRate(Double.parseDouble(cursor.getString(5)));
                workday.setResult(Double.parseDouble(cursor.getString(6)));
                workDayList.add(workday);
            } while (cursor.moveToNext());
        }
        return workDayList;
    }

    public int updateWorkday (WorkDay workday) {
        SQLiteDatabase db = this.getWritableDatabase();

        ContentValues values = new ContentValues();
        values.put(KEY_DAY, workday.getDay());
        values.put(KEY_MONTH, workday.getMonth());
        values.put(KEY_YEAR, workday.getYear());
        values.put(KEY_HOURS, workday.getHours());
        values.put(KEY_RATE, workday.getRate());
        values.put(KEY_RESULT, workday.getResult());

        return db.update(TABLE_WORKDAYS, values, KEY_ID + " = ?",
                new String[] { String.valueOf(workday.getId()) });
    }

    public void deleteWorkDay (WorkDay workDay) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_WORKDAYS, KEY_ID + "  = ?",
                new String[] { String.valueOf(workDay.getId()) });
        db.close();
        return;
    }
}