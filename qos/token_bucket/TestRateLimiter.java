import com.google.common.util.concurrent.RateLimiter;
 
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
 

public class TestRateLimiter {
 
    public static void main(String[] args) {
 
        //新建一个每秒限制3个的令牌桶
        RateLimiter rateLimiter = RateLimiter.create(4);
 
        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(100);
        for (int i = 0; i < 100; i++) {
            executor.execute(new Runnable() {
                @Override
                public void run() {
                    //获取令牌桶中一个令牌，最多等待10秒
                    if (rateLimiter.tryAcquire(10, 10, TimeUnit.SECONDS)) {
                        System.out.println(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
                    }
                }
            });
        }
 
        executor.shutdown();
    }
}