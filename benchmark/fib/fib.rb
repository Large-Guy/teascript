def fib(n)
    if n < 2 then
        n
    else
        fib(n - 1) + fib(n - 2)
    end
end

start = Time.now

puts fib(35)

puts "elapsed: " + (Time.now - start).to_s