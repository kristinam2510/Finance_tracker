<?php
header('Content-Type: application/json');


$requestMethod = $_SERVER["REQUEST_METHOD"];
$data = json_decode(file_get_contents('php://input'), true);


$filename = 'transactions.txt';

switch ($requestMethod) {
    case 'GET':
        if (file_exists($filename)) {
            $transactions = file($filename, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
            echo json_encode($transactions);
        } else {
            echo json_encode([]);
        }
        break;

    case 'POST':
        if ($data) {
            $transactionLine = implode(' ', [
                $data['category'],
                $data['amount'],
                $data['date'],
                $data['isCredit'] ? 'Credit' : 'Debit'
            ]);
            file_put_contents($filename, $transactionLine . PHP_EOL, FILE_APPEND);
            echo json_encode(['status' => 'success']);
        } else {
            echo json_encode(['status' => 'error']);
        }
        break;

    default:
        echo json_encode(['status' => 'method not allowed']);
        break;
}
?>
