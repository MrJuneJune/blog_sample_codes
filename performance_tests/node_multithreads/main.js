const { Worker } = require('worker_threads');

const start = 0;
const end = 100_000_000; 
const numberOfCpus = 4;
const rangePerWorker = Math.ceil((end - start + 1) / numberOfCpus);

console.log(`Prime number from ${start} to ${end} using ${numberOfCpus} workers...`);

let completedWorkers = 0;
const primes = [];

for (let i = 0; i < numberOfCpus; i++) {
  const workerStart = start + i * rangePerWorker;
  const workerEnd = Math.min(workerStart + rangePerWorker - 1, end);

  const worker = new Worker('./worker.js', {
    workerData: { start: workerStart, end: workerEnd },
  });

  worker.on('message', (workerPrimes) => {
    // Fun fact: there is maximum argument count in js huh....
    // primes.push(...workerPrimes);
    completedWorkers++;

    if (completedWorkers === numberOfCpus) {
      console.log('All workers completed.');
    }
  });
}
