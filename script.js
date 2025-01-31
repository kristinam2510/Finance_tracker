let transactions = [];

//display transactions in the list
function displayTransactions() {
    const transactionList = document.getElementById('transaction-list');
    transactionList.innerHTML = ''; 

    transactions.forEach((trans, index) => {
        const li = document.createElement('li');
        li.textContent = `${trans.category} - $${trans.amount} on ${trans.date} (${trans.isCredit ? 'Credit' : 'Debit'})`;
        li.dataset.index = index; 
        transactionList.appendChild(li);
    });
}

//adding a transaction
document.getElementById('transaction-form').addEventListener('submit', function(event) {
    event.preventDefault();

    const category = document.getElementById('category').value;
    const amount = parseFloat(document.getElementById('amount').value);
    const date = document.getElementById('date').value;
    const type = document.getElementById('type').value;

    const isCredit = type === 'c';

    //request to add the transaction
    fetch('backend.php', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ category, amount, date, isCredit })
    })
    .then(response => response.json())
    .then(data => {
        if (data.status === 'success') {
            transactions.push({ category, amount, date, isCredit });
            displayTransactions();
            alert('Transaction added successfully!');
            document.getElementById('transaction-form').reset(); 
        } else {
            alert('Failed to add transaction.');
        }
    })
    .catch(error => console.error('Error:', error));
});

//load transactions on page
function loadTransactions() {
    fetch('backend.php')
        .then(response => response.json())
        .then(data => {
            transactions = data.map(trans => {
                const parts = trans.split(' ');
                return {
                    category: parts[0],
                    amount: parseFloat(parts[1]),
                    date: parts[2],
                    isCredit: parts[3] === 'Credit'
                };
            });
            displayTransactions();
        })
        .catch(error => console.error('Error loading transactions:', error));
}

//delete a selected transaction
document.getElementById('delete-button').addEventListener('click', function() {
    const indexToDelete = prompt("Enter the index of the transaction to delete (1-based):");
    if (indexToDelete && transactions[indexToDelete - 1]) {
        transactions.splice(indexToDelete - 1, 1);
        displayTransactions();
        alert('Transaction deleted successfully!');
    } else {
        alert('Invalid transaction index.');
    }
});

//financial summary
document.getElementById('summary-button').addEventListener('click', function() {
    const totalIncome = transactions.filter(t => t.isCredit).reduce((sum, t) => sum + t.amount, 0);
    const totalExpenses = transactions.filter(t => !t.isCredit).reduce((sum, t) => sum + t.amount, 0);
    const savings = totalIncome - totalExpenses;
    
    alert(`Total Income: $${totalIncome}\nTotal Expenses: $${totalExpenses}\nSavings: $${savings}`);
});

//Load transactions when the page is loaded
window.onload = loadTransactions;
