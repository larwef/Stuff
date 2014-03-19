package com.lartek.wagecalculator20;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class WorkDay implements Comparable<WorkDay> {
    int id;
    int day;
    int month;
    int year;
    double hours;
    double rate;
    double result;

    public WorkDay(){
    }
    public WorkDay(int id, int day, int month, int year, double hours, double rate, double result){
        this.id = id;
        this.day = day;
        this.month = month;
        this.year = year;
        this.hours = hours;
        this.rate = rate;
        this.result = result;
    }
    public WorkDay(int day, int month, int year, double hours, double rate, double result){
        this.day = day;
        this.month = month;
        this.year = year;
        this.hours = hours;
        this.rate = rate;
        this.result = result;
    }

    public void setId (int id){
        this.id = id;
    }
    public int getId(){
        return id;
    }
    public void setDay(int day) {
        this.day = day;
    }
    public int getDay() {
        return day;
    }
    public void setMonth(int month) {
        this.month = month;
    }
    public int getMonth() {
        return month;
    }
    public void setYear (int year) {
        this.year = year;
    }
    public int getYear () {
        return year;
    }
    public void setHours (double hours) {
        this.hours = hours;
    }
    public double getHours () {
        return hours;
    }
    public void setRate (double rate) {
        this.rate = rate;
    }
    public double getRate () {
        return rate;
    }
    public void setResult (double result) {
        this.result = result;
    }
    public double getResult () {
        return result;
    }

    @Override
    public int compareTo (WorkDay wd) {
        if (this.year == wd.year) {
            if (this.month == wd.month){
                return (this.day - wd.day);
            }
            return (this.month - wd.month);
        }
        return (this.year - wd.year);
    }
}
