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
                dir('scripts')
                {
                sh 'deploy_with_ansible.sh'
                }
                
            }
        }
    }
}
