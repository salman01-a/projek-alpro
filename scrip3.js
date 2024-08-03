const menuItems = [
    { kode: 'a', nama: 'Spicy Floss', harga: 12500 },
    { kode: 'b', nama: 'Sausage Diva', harga: 12500 },
    { kode: 'c', nama: 'Floss Roll', harga: 14500 },
    { kode: 'd', nama: 'Choco Meises', harga: 12500 },
    { kode: 'e', nama: 'Rendang Floss', harga: 12500 },
    { kode: 'f', nama: 'Milky Bun', harga: 9000 },
    { kode: 'g', nama: 'Coffee Bun', harga: 12000 },
    { kode: 'h', nama: 'Choco Bun', harga: 9000 },
    { kode: 'i', nama: 'Sugar Pillow', harga: 10000 },
    { kode: 'j', nama: 'Banana Choco Cheese', harga: 12500 }
];

let orders = [];

function showSection(sectionId) {
    hideAllSections();
    document.getElementById(sectionId).style.display = 'block';
    if (sectionId === 'orderMenu') displayMenuItems();
    if (sectionId === 'orderSummary') displayOrders();
    if (sectionId === 'editMenu') displayEditOrders();
}
 
function hideAllSections() {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => section.style.display = 'none');
}

function displayMenuItems() {
    const menuSelect = document.getElementById('menuSelect');
    menuSelect.innerHTML = menuItems.map(item => `<option value="${item.kode}">${item.nama} - Rp. ${item.harga}</option>`).join('');
}

function addOrder() {
    const orderName = document.getElementById('orderName').value;
    const menuSelect = document.getElementById('menuSelect');
    const orderQuantity = document.getElementById('orderQuantity').value;
    if (orderName && orderQuantity > 0) {
        const selectedItem = menuItems.find(item => item.kode === menuSelect.value);
        const order = {
            kode: selectedItem.kode,
            nama: selectedItem.nama,
            jumlah: parseInt(orderQuantity),
            atasNama: orderName,
            harga: selectedItem.harga,
            total: selectedItem.harga * parseInt(orderQuantity)
        };
        orders.push(order);
        alert('Pesanan berhasil ditambahkan!');
    } else {
        alert('Silakan masukkan nama dan jumlah yang valid.');
    }
}

function displayOrders() {
    const orderTable = document.getElementById('orderTable');
    orderTable.innerHTML = orders.map((order, index) => `
        <tr>
            <td>${index + 1}</td>
            <td>${order.kode}</td>
            <td>${order.nama}</td>
            <td>${order.jumlah}</td>
            <td>${order.atasNama}</td>
            <td>${order.harga}</td>
            <td>${order.total}</td>
        </tr>
    `).join('');
}

function searchOrder() {
    const searchName = document.getElementById('searchName').value.toLowerCase();
    const searchResult = document.getElementById('searchResult');
    const foundOrders = orders.filter(order => order.atasNama.toLowerCase() === searchName);
    if (foundOrders.length > 0) {
        searchResult.innerHTML = foundOrders.map((order, index) => `
            <p>${index + 1}. Kode: ${order.kode}, Nama Roti: ${order.nama}, Jumlah: ${order.jumlah}, Harga: ${order.harga}, Total: ${order.total}</p>
        `).join('');
    } else {
        searchResult.innerHTML = '<p>Tidak ada pesanan ditemukan atas nama tersebut.</p>';
    }
}

function displayEditOrders() {
    const editOrders = document.getElementById('editOrders');
    editOrders.innerHTML = orders.map((order, index) => `
        <div>
            <p>${index + 1}. Kode: ${order.kode}, Nama Roti: ${order.nama}, Jumlah: <input type="number" id="editQuantity${index}" value="${order.jumlah}" min="1">, Atas Nama: <input type="text" id="editName${index}" value="${order.atasNama}">
            <button onclick="editOrder(${index})">Simpan</button>
            <button onclick="deleteOrder(${index})">Hapus</button></p>
        </div>
    `).join('');
}

function editOrder(index) {
    const editQuantity = document.getElementById(`editQuantity${index}`).value;
    const editName = document.getElementById(`editName${index}`).value;
    if (editQuantity > 0 && editName) {
        orders[index].jumlah = parseInt(editQuantity);
        orders[index].atasNama = editName;
        orders[index].total = orders[index].jumlah * orders[index].harga;
        alert('Pesanan berhasil diperbarui!');
        displayOrders();
    } else {
        alert('Silakan masukkan nama dan jumlah yang valid.');
    }
}

function deleteOrder(index) {
    orders.splice(index, 1);
    alert('Pesanan berhasil dihapus!');
    displayOrders();
    displayEditOrders();
}

function showPaymentDetails() {
    const payName = document.getElementById('payName').value.toLowerCase();
    const paymentDetails = document.getElementById('paymentDetails');
    const foundOrders = orders.filter(order => order.atasNama.toLowerCase() === payName);
    if (foundOrders.length > 0) {
        const totalPayment = foundOrders.reduce((total, order) => total + order.total, 0);
        paymentDetails.innerHTML = `
            <p>Total Pembayaran: Rp. ${totalPayment}</p>
            <p>Rincian Pesanan:</p>
            ${foundOrders.map((order, index) => `
                <p>${index + 1}. Kode: ${order.kode}, Nama Roti: ${order.nama}, Jumlah: ${order.jumlah}, Harga: ${order.harga}, Total: ${order.total}</p>
            `).join('')}
        `;
    } else {
        paymentDetails.innerHTML = '<p>Tidak ada pesanan ditemukan atas nama tersebut.</p>';
    }
}

function toggleCashInput(show) {
    document.getElementById('cashInput').style.display = show ? 'block' : 'none';
}

function payOrder() {
    const payName = document.getElementById('payName').value.toLowerCase();
    const paymentMethod = document.querySelector('input[name="paymentMethod"]:checked').value;
    const foundOrders = orders.filter(order => order.atasNama.toLowerCase() === payName);
    if (foundOrders.length > 0) {
        const totalPayment = foundOrders.reduce((total, order) => total + order.total, 0);
        if (paymentMethod === 'cash') {
            const cashAmount = parseInt(document.getElementById('cashAmount').value);
            if (cashAmount >= totalPayment) {
                const change = cashAmount - totalPayment;
                document.getElementById('paymentSummary').innerHTML = `<p>Total Bayar: Rp. ${totalPayment}, Uang Tunai: Rp. ${cashAmount}, Kembalian: Rp. ${change}</p>`;
                showPopup();
            } else {
                alert('Jumlah uang tunai tidak mencukupi.');
            }
        } else {
            document.getElementById('paymentSummary').innerHTML = `<p>Total Bayar: Rp. ${totalPayment}, Metode Pembayaran: Debit</p>`;
            showPopup();
        }
        orders = orders.filter(order => order.atasNama.toLowerCase() !== payName);
    } else {
        alert('Tidak ada pesanan ditemukan atas nama tersebut.');
    }
}

function resetOrders() {
    orders = [];
    alert('Semua pesanan telah di-reset.');
    displayOrders();
}

function showPopup() {
    document.getElementById('paymentSuccessPopup').classList.remove('hidden');
}

function closePopup() {
    document.getElementById('paymentSuccessPopup').classList.add('hidden');
}
