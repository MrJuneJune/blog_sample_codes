const { parentPort, workerData } = require('worker_threads');

const { start, end } = workerData;

function isPrime(num) {
  if (num < 2) { 
    return false;
  }
  for (let i = 2, sqrt = Math.sqrt(num); i <= sqrt; i++) {
    if (num % i === 0) { 
      return false;
    }
  }
  return true;
}

const primes = [];
for (let i = start; i <= end; i++) {
  if (isPrime(i)) primes.push(i);
}

parentPort.postMessage(primes);
