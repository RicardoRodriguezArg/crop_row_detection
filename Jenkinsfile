pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Ansible Deploy') {
            steps {
                echo 'Deploying....'
                ansiblePlaybook colorized: true, 
            	credentialsId: 'ssh-jenkins',
            	limit: "${HOST_PROVISION}",
            	installation: 'ansible',
            	
            	playbook: 'playbook/playbook.yml', 
            	sudo: true,
				sudoUser: 'jenkins'
            }
        }
    }
}
