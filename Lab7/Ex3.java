package Lab7;

class Time {
    public int hours, minutes, seconds, total;

    public Time(int a, int b, int c) {
        hours = a;
        minutes = b;
        seconds = c;
        total = a * 3600 + b * 60 + c;
    }

    public Time(int a, int b) {
        this(a, b, 0);
    }

    public Time(int a) {
        this(a, 0, 0);
    }

    public Time inc() {
        total += 1;
        hours = total / 3600;
        minutes = (total - hours * 3600) / 60;
        seconds = (total - hours * 3600 - minutes * 60);
        return this;
    }
}

class TimeCreator {
    Time t;

    public Time createTime(int a, int b, int c) {
        return new Time(a, b, c);
    }
    public Time createTime(int a, int b) {
        return createTime(a, b, 0);
    }
    public Time createTime(int a) {
        return createTime(a, 0, 0);
    }
}



public class Ex3 {
    public static Time time_difference (Time a, Time b) {
        int total1 = a.total;
        int total2 = b.total;

        int total_result = java.lang.Math.abs(total1 - total2);
        int total_hours = total_result / 3600;
        total_result %= 3600;
        int total_minutes = total_result / 60;
        total_result %= 60;
        int total_seconds = total_result;

        Time result = new Time(total_hours, total_minutes, total_seconds);
        return result;
    }

    public static void main (String[] args) {
        TimeCreator t = new TimeCreator();
        Time t1 = t.createTime(11, 59, 59);
        Time t2 = t.createTime(16, 40);
        t1.inc().inc();
        System.out.println("Time1 is " + t1.hours + " " + t1.minutes + " " + t1.seconds);
        System.out.println("Time2 is " + t2.hours + " " + t2.minutes + " " + t2.seconds);

        Time tdelta = time_difference(t1, t2);
        System.out.println("Time delta is " + tdelta.hours + " " + tdelta.minutes + " " + tdelta.seconds);
    }
}
