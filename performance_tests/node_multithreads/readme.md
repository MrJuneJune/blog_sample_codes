# Multithreading in JavaScript

I recently discussed various programming languages and their advantages with my new coworkers at Meta. During our conversation, we debated the topic of multithreading in JavaScript. My stance was that multithreading became possible in Node.js after certain versions, while my coworker believed it wasn't feasible due to JavaScript's original design. This led me to delve deeper into the topic and provide some code examples.

#### History and Design Choices

JavaScript is inherently a **single-threaded** system. It has one call stack, one memory heap, and executes code sequentially. According to Brendan Eich, the creator of JavaScript, it was meant to be a simple language for "people who don’t know what a compiler is." Initially, JavaScript was regarded as a "cursed" language because it was primarily used for annoying pop-up ads and flashy animations. This eventually prompted Firefox to impose restrictions on such features.

Interestingly (and off tangent), Eich mentioned that JavaScript was designed as a starting point, with the expectation that developers would eventually transition to "real" languages. This idea mirrors other ecosystems like Microsoft's BASIC leading to C++ or JavaScript serving as an entry point to Java. Despite its C-like syntax, JavaScript's connection to Java is superficial, adding to its unique identity.

For more context, check out [this short but fascinating interview with Brendan Eich](https://www.youtube.com/watch?v=IPxQ9kEaF8c).

Fast forward to Ryan Dahl’s creation of Node.js, which uses the **event-driven, non-blocking I/O** model with a **single-threaded** event loop. Built on top of the V8 engine, Node.js compiles JavaScript into machine code at runtime. Today, it's the backbone of server-side JavaScript applications like Next.js, Remix, Express, and more. Thanks to the V8 engine (thank you C++), JavaScript is surprisingly fast for a scripting language. (And no, I won't link stupid "programming" dumb ball bouncing around doing billion nested loop).

However, V8 doesn't natively support multithreading in JavaScript because it processes everything within a **single-threaded**. In browsers like Chrome, for instance, each tab operates as an independent process, which prevents interference between tabs. Traditionally, developers have relied on tools like PM2 or other process managers to launch multiple Node.js instances to handle large workloads. This workaround sufficed for many use cases.

#### So.. is Multithreading Possible Now?

The short answer is yes. Node.js supports multithreading through the **Worker Threads** module, introduced in Node.js 10.5.0 (June 20, 2018) and stabilized in Node.js 12. I didn’t pay much attention to this feature until last year when I had to run an FFmpeg command to process videos and audios. (I really hope that code is still alive... ) 

The advent of **SharedArrayBuffer** and **Atomics** APIs in V8 enabled native multithreading capabilities (thank you C++). Node.js developers complemented these changes by adding thread-safe capabilities to core libraries, making it possible to safely share data between threads.

#### Example of Multithreading in Node.js

Here’s a simple program to calculate all prime numbers between 0 and 1 billion using 4 CPUs. (I'm using WSL2 and am slightly ashamed of coding on Windows—a "toy OS." Then again, we're also using a "toy language," so it balances out!)

**`main.js`:**
```javascript
const { Worker } = require('worker_threads');

const start = 0;
const end = 1_000_000_000;
const numberOfCpus = 4;
const rangePerWorker = Math.ceil((end - start + 1) / numberOfCpus);

console.log(`Calculating prime numbers from ${start} to ${end} using ${numberOfCpus} workers...`);

let completedWorkers = 0;
const primes = [];

for (let i = 0; i < numberOfCpus; i++) {
  const workerStart = start + i * rangePerWorker;
  const workerEnd = Math.min(workerStart + rangePerWorker - 1, end);

  const worker = new Worker('./worker.js', {
    workerData: { start: workerStart, end: workerEnd },
  });

  worker.on('message', (workerPrimes) => {
    primes.push(...workerPrimes);
    completedWorkers++;

    if (completedWorkers === numberOfCpus) {
      console.log('All workers completed.');
    }
  });

  worker.on('error', (err) => console.error(`Worker error: ${err}`));
  worker.on('exit', (code) => {
    if (code !== 0) console.error(`Worker stopped with exit code ${code}`);
  });
}
```

**`worker.js`:**
```javascript
const { parentPort, workerData } = require('worker_threads');

const { start, end } = workerData;

function isPrime(num) {
  if (num < 2) return false;
  for (let i = 2, sqrt = Math.sqrt(num); i <= sqrt; i++) {
    if (num % i === 0) return false;
  }
  return true;
}

const primes = [];
for (let i = start; i <= end; i++) {
  if (isPrime(i)) primes.push(i);
}

parentPort.postMessage(primes);
```

**Result:**
As expected, all 4 cores are utilized. Interestingly, one core finished significantly earlier than the others because it was handling a smaller computational load (0 to 250 million). I noticed some random spikes at the end—probably due to system-level resource allocation quirks.
