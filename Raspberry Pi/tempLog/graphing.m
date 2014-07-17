clear

file = fopen('tempLog.txt');

data = [];
year = [];
month = [];
day = [];
hour = [];
minute = [];
i = 1;

tline = fgetl(file);
while ischar(tline)
    line = strsplit(tline);
    data(i) = str2double(line(3));
    
    date = strsplit(num2str(cell2mat(line(1))), '/');
    year(i) = str2double(date(3));
    month(i) = str2double(date(2));
    day(i) = str2double(date(1));
    
    time = strsplit(num2str(cell2mat(line(2))), ':');
    hour(i) = str2double(time(1));
    minute(i) = str2double(time(2));
    
    i = i + 1;
    tline = fgetl(file);
end
fclose(file);

xdate = datenum(year, month, day, hour, minute, minute);
plot(xdate, data, 'o-');
xlabel('Time');
ylabel('Temperature [C^{\circ}]');
datetick('x', 'mm-dd HH:MM', 'keepticks');

grid on;