var ctx = document.getElementById("chart");
var myChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: ["C++", "C", "Java", "JavaScript", "Python"],
        datasets: [{
            label: 'Programming Ability',
            data: [20, 18, 6, 5, 2],
            backgroundColor: [
                'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
                'rgba(132, 111, 178, 0.2)'
            ],
            borderColor: [
                'rgba(255,99,132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
                'rgba(132, 111, 178, 1)'
            ],
            borderWidth: 3
        }]
    },
    options: {
        scales: {
            yAxis: [{
                ticks: {
                    beginAtZero: true
                }
            }]
        }
    }
});