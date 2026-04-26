function fibonacci(n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

function fibonacci_dm(n, memo = {}) {
    if (n in memo) {
        return memo[n];
    }
    if (n <= 1) {
        return BigInt(n);
    }
    memo[n] = fibonacci_dm(n - 1, memo) + fibonacci_dm(n - 2, memo);
    return memo[n];
}

// Example usage:
// console.log(fibonacci(300));

// Example usage:
console.log(fibonacci_dm(300));
console.log(fibonacci_dm(301));

